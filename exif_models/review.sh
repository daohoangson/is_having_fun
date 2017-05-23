#!/bin/sh

docker run \
	-v "$PWD:/var/www/html" \
	-v "/Users:/Users:ro" \
	-p 8080:80 \
	--rm xfrocks/docker-xenforo:php-apache-7.1.0