package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"os"
)

var rawFile *os.File

func main() {
	rawFile, _ = os.Create("data.raw")
	defer rawFile.Close()

	http.HandleFunc("/samples", samples)
	fmt.Println("Starting server...")

	path, err := os.Getwd()
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(path)

	http.ListenAndServe(":5003", nil)
}

func samples(res http.ResponseWriter, req *http.Request) {
	b, err := ioutil.ReadAll(req.Body)
	if err != nil {
		panic(err)
	}

	n, err := rawFile.Write(b)

	fmt.Println(n)

	if n == 0 || err != nil {
		panic(err)
	}

	rawFile.Sync()
}
