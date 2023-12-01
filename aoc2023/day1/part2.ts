import { readFileSync } from "fs";

function digit(line: string): string | undefined {
  const m = line.match(/^([0-9]|one|two|three|four|five|six|seven|eight|nine)/);
  if (m !== null) {
    const found = m[1];
    switch (found) {
      case "one":
        return "1";
      case "two":
        return "2";
      case "three":
        return "3";
      case "four":
        return "4";
      case "five":
        return "5";
      case "six":
        return "6";
      case "seven":
        return "7";
      case "eight":
        return "8";
      case "nine":
        return "9";
    }

    return found;
  }
}

function firstOf(line: string): string {
  for (let i = 0; i < line.length; i++) {
    const d = digit(line.substring(i));
    if (typeof d === "string") {
      return d;
    }
  }

  throw new Error(`There is no digit in ${line}`);
}

function lastOf(line: string): string {
  for (let i = line.length; i > -1; i--) {
    const d = digit(line.substring(i));
    if (typeof d === "string") {
      return d;
    }
  }

  throw new Error(`There is no digit in ${line}`);
}

(async function main() {
  const input: string = readFileSync("day1/input.txt", "utf8");
  const lines = input.split("\n").filter((line) => line.length > 0);
  let sum = 0;
  for (const line of lines) {
    sum += parseInt(firstOf(line) + lastOf(line), 10);
  }
  console.log({ sum });
})();
