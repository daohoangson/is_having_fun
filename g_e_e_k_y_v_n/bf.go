package main

import (
	"bytes"
	"crypto/md5"
	"encoding/json"
	"fmt"
	"io"
	"io/ioutil"
	"net/http"
	"net/url"
	"os"
)

type PageData struct {
	Status string
	Content string
}

func download_page(page int) {
	file_name := fmt.Sprintf("page_%04d.txt", page)
	url := fmt.Sprintf("http://www.piday.org/apps/million/fetch.php?page=%d", page)

	// check for output file, skip downloading if possible
	file_test, err := os.Open(file_name)
	if (err == nil) {
		defer file_test.Close()
		fmt.Printf("download_page(%d): file %s exists, do nothing\n", page, file_name)
	} else {
		fmt.Printf("download_page(%d): url=%s\n", page, url)
	}

	// download the file from remote server
	resp, err := http.Get(url)
	if (err != nil) {
		fmt.Printf("download_page(%d) -> http.Get failed: %s\n", page, err)
		return
	}
	defer resp.Body.Close()

	// get response as string
	body, err := ioutil.ReadAll(resp.Body)
	if (err != nil) {
		fmt.Printf("download_page(%d) -> ioutil.ReadAll failed: %s\n", page, err)
		return
	}

	// parse response (JSON)
	var data PageData
	err = json.Unmarshal(body, &data)
	if (err != nil) {
		fmt.Printf("download_page(%d) -> json.Unmarshal(%s) failed: %s\n", page, body, err)
		return
	}

	// save to file for later usage
	file_out, err := os.Create(file_name)
	if (err != nil) {
		fmt.Printf("download_page(%d) -> os.Create(%s) failed: %s\n", page, file_name, err)
		return
	}
	defer file_out.Close()

	// actually write the file content
	var content []byte
	if page == 1 {
		// ignore 2 first characters for the first page
		content = []byte(data.Content[2:])
	} else {
		if page == 1001 {
			// only care about the 2 first characters for the last page
			content = []byte(data.Content[:2])
		} else {
			content = []byte(data.Content)
		}
	}
	file_out.Write(content)
}

func run(routines int, value_min int, value_max int, f func(int)) {
	chan_value := make(chan int, routines)
	chan_done := make(chan int, routines)

	// create some goroutines as requested
	for ri := 0; ri < routines; ri++ {
		go func() {
			should_continue := true
			for should_continue {
				value := <- chan_value
				if (value > 0) {
					f(value)
				} else {
					should_continue = false
				}
			}

			chan_done <- 1
		} ()
	}

	// start sending value requests
	for value := value_min; value <= value_max; value++ {
		chan_value <- value
	}
	// send terminal requests
	for ri := 0; ri < routines; ri++ {
		chan_value <- 0
	}

	// wait for goroutines to die
	for ri := 0; ri < routines; ri++ {
		<- chan_done
	}
}

func download_pages(routines int) {
	run(routines, 1, 1001, download_page)
}

var get_digits_cached []string
var get_digits_sem chan int

func get_digits(digits_count int) (string, error) {
	// we need to use semaphore here to read the file properly
	get_digits_sem <- 1

	var buffer bytes.Buffer
	page := 1

	if len(get_digits_cached) == 0 {
		get_digits_cached = make([]string, 1001)
	}

	for buffer.Len() < digits_count {
		var content []byte

		if len(get_digits_cached[page]) == 0 {
			file_name := fmt.Sprintf("page_%04d.txt", page)
			file_in, err := os.Open(file_name)
			if err != nil {
				<- get_digits_sem
				return "", err
			}

			content, err = ioutil.ReadAll(file_in)
			file_in.Close()

			if err != nil {
				<- get_digits_sem
				return "", err
			}

			get_digits_cached[page] = string(content)
		} else {
			content = []byte(get_digits_cached[page])
		}

		needed := digits_count - buffer.Len()
		if len(content) > needed {
			buffer.Write(content[:needed])
		} else {
			buffer.Write(content)
		}

		page++
	}

	<- get_digits_sem

	return buffer.String(), nil
}

func send_request(digits_count int) {
	digits, err := get_digits(digits_count)
	if err != nil {
		fmt.Printf("send_request(%d) -> get_digits failed: %s\n", digits_count, err)
		os.Exit(1)
	}

	h := md5.New()
	io.WriteString(h, digits)
	digits_md5 := fmt.Sprintf("%x", h.Sum(nil))

	values := make(url.Values)
	values.Set("email", "email@domain.com")
	values.Set("key", digits_md5)
	resp, err := http.PostForm("http://www.geeky.vn/register.php", values)
	if (err != nil) {
		fmt.Printf("send_request(%d) -> http.PostForm(%d) failed: %s\n", digits_count, digits_md5, err)
		os.Exit(1)
	}
	defer resp.Body.Close()

	// get response as string
	body, err := ioutil.ReadAll(resp.Body)
	if (err != nil) {
		fmt.Printf("send_request(%d) -> ioutil.ReadAll failed: %s\n", digits_count, err)
		os.Exit(1)
	}

	body_str := string(body)
	fmt.Printf("send_request(%d) -> %s\n", digits_count, body_str)
	if body_str != "0" {
		os.Exit(0)
	}
}

func bf(routines int, bf_start int) {
	run(routines, bf_start, 1000000, send_request)
}

func main() {
	routines := 25
	get_digits_sem = make(chan int, 1)

	download_pages(routines)
	bf(routines, 100000)
}