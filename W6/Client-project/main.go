package main

import (
	"fmt"
	"log"
	"math/rand"
	"net/http"
	"sync"
	"time"
)

type Client struct {
	ID int
}

type Metrics struct {
	mu               sync.Mutex
	totalRequests    int
	totalTime        float64
	totalPerformance float64
}

func (m *Metrics) AddRequest(duration, performance float64) {
	m.mu.Lock()
	defer m.mu.Unlock()
	m.totalRequests++
	m.totalTime += duration
	m.totalPerformance += performance
}

func (m *Metrics) Report() {
	m.mu.Lock()
	defer m.mu.Unlock()
	if m.totalRequests == 0 {
		fmt.Println("\n--- Load Balancer Performance Report ---")
		fmt.Println("No requests were successfully processed.")
		fmt.Println("----------------------------------------")
		return
	}

	avgTime := m.totalTime / float64(m.totalRequests)
	avgPerformance := m.totalPerformance / float64(m.totalRequests)
	fmt.Println("\n--- Load Balancer Performance Report ---")
	fmt.Printf("Total requests: %d\n", m.totalRequests)
	fmt.Printf("Average response time: %.2fs\n", avgTime)
	fmt.Printf("Average performance: %.2f\n", avgPerformance)
	fmt.Println("----------------------------------------")
}

func (c *Client) SendRequests(wg *sync.WaitGroup, serverAddr string, metrics *Metrics) {
	defer wg.Done()

	for i := 0; i < 400; i++ {
		load := rand.Float64()
		start := time.Now()

		resp, err := http.Get(serverAddr)
		if err != nil {
			log.Printf("Client %d: Unable to connect. Skipping request.\n", c.ID)
			time.Sleep(10 * time.Millisecond)
			continue
		}
		resp.Body.Close()

		duration := time.Since(start).Seconds()
		performance := duration - load

		metrics.AddRequest(duration, performance)
		fmt.Printf("Client %d: Response time: %.2fs, Performance: %.2f\n", c.ID, duration, performance)
	}
}

func main() {
	rand.Seed(time.Now().UnixNano())

	serverAddr := "http://localhost:8080"
	metrics := &Metrics{}
	numClients := 50 // Change for different batch sizes

	var wg sync.WaitGroup
	for i := 0; i < numClients; i++ {
		client := &Client{ID: i}
		wg.Add(1)
		go client.SendRequests(&wg, serverAddr, metrics)
	}

	fmt.Printf("Generated %d clients. Sending requests to %s\n", numClients, serverAddr)
	wg.Wait()

	metrics.Report()
}
