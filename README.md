# Queuing Systems 

Project of the "Queuing Systems" course at School of ECE NTUA.

Considering a M/M/2/10 Queuing System with 2 servers and 10 maximum clients, including those who are currently served. As long as clients are less or equal to **k** (k=1,2,..,9), they are all served by server **α** and **β** is idle. Server **β** is only activated if the threshold **k** is surpassed.

![1](https://user-images.githubusercontent.com/20473840/35744249-8e6c5958-0848-11e8-944a-81ca750b73e2.png)

In our system we have Poisson arrivals, with different arrival rates ( **λ** = 1,2,3 customers/sec) and exponential service rates **μ<sub>α</sub>** = 4 customers/sec and **μ<sub>β</sub>** = 1 customer/sec

Using Markov Chain Simulation,we calculate:
* Average number of clients
* Throughput in both servers
