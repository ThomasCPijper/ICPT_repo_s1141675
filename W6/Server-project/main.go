package main

import (
	"fmt"
	"log"
	"math/rand"
	"net/http"
	"sync"
	"time"
)

type Server struct {
	ID             int
	ActiveRequests int
	Weight         int
	mu             sync.Mutex
}

type LoadBalancer struct {
	Servers      []*Server
	RequestQueue chan RequestWrapper
	Algorithm    string
	counter      int
	mu           sync.Mutex
}

type RequestWrapper struct {
	Request  *http.Request
	Response http.ResponseWriter
}

func (lb *LoadBalancer) RoundRobin() *Server {
	lb.mu.Lock()
	defer lb.mu.Unlock()

	server := lb.Servers[lb.counter%len(lb.Servers)]
	lb.counter++
	return server
}

func (lb *LoadBalancer) LeastConnections() *Server {
	lb.mu.Lock()
	defer lb.mu.Unlock()

	var selected *Server
	minConnections := int(^uint(0) >> 1)
	for _, server := range lb.Servers {
		server.mu.Lock()
		if server.ActiveRequests < minConnections {
			minConnections = server.ActiveRequests
			selected = server
		}
		server.mu.Unlock()
	}
	return selected
}

func (lb *LoadBalancer) WeightedRoundRobin() *Server {
	lb.mu.Lock()
	defer lb.mu.Unlock()

	totalWeight := 0
	for _, server := range lb.Servers {
		totalWeight += server.Weight
	}
	lb.counter = (lb.counter + 1) % totalWeight

	currentWeight := 0
	for _, server := range lb.Servers {
		currentWeight += server.Weight
		if lb.counter < currentWeight {
			return server
		}
	}

	return lb.Servers[0]
}

func (lb *LoadBalancer) SelectServer() *Server {
	switch lb.Algorithm {
	case "least_connections":
		return lb.LeastConnections()
	case "weighted_round_robin":
		return lb.WeightedRoundRobin()
	default:
		return lb.RoundRobin()
	}
}

func (lb *LoadBalancer) forwardToServer(rw RequestWrapper) {
	server := lb.SelectServer()

	server.mu.Lock()
	server.ActiveRequests++
	server.mu.Unlock()

	load := rand.Float64()
	time.Sleep(time.Duration(load*1000) * time.Millisecond)

	server.mu.Lock()
	server.ActiveRequests--
	server.mu.Unlock()

	response := fmt.Sprintf("Server %d handled the request. Load: %.2f", server.ID, load)
	fmt.Fprintln(rw.Response, response)
	log.Println(response)
}

func (lb *LoadBalancer) start() {
	for {
		rw := <-lb.RequestQueue

		go lb.forwardToServer(rw)
	}
}

func (lb *LoadBalancer) handleRequest(w http.ResponseWriter, r *http.Request) {
	rw := RequestWrapper{
		Request:  r,
		Response: w,
	}

	select {
	case lb.RequestQueue <- rw:
		log.Println("Request added to queue")
	default:
		http.Error(w, "Load balancer is overloaded", http.StatusServiceUnavailable)
	}
}

func main() {
	rand.Seed(time.Now().UnixNano())

	numServers := 5
	servers := make([]*Server, numServers)
	for i := 0; i < numServers; i++ {
		servers[i] = &Server{
			ID:     i,
			Weight: rand.Intn(5) + 1, // Assign random weights for Weighted Round Robin
		}
		fmt.Printf("Server %d initialized with weight %d\n", i, servers[i].Weight)
	}

	lb := &LoadBalancer{
		Servers:      servers,
		RequestQueue: make(chan RequestWrapper, 100),
		Algorithm:    "round_robin", // Choose the algorithm: "round_robin", "least_connections", or "weighted_round_robin"
	}

	go lb.start()

	http.HandleFunc("/", lb.handleRequest)

	port := ":8080"
	fmt.Printf("Load balancer started on port %s with %d servers using algorithm: %s\n", port, numServers, lb.Algorithm)
	log.Fatal(http.ListenAndServe(port, nil))
}
