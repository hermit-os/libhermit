---
layout:     post
title:      Go support
author:     Stefan Lankes
tags: 	    go
subtitle:   Integration of the Go Runtime
---

Today, the support of the Go runtime is merged into the master branch.
As Go demo, I added a simple echo server from the book
*[The Go Programming Language](http://www.gopl.io)*.
In principle, the whole Go runtime is supported. However, HermitCore is a single
address-space operating system, which means, that in final consequence the support
of processes is missing. Consequently, any support of process creation or
inter-process communication isn't realized in our Go runtime.
Furthermore, the IPv6 support is currently not available. But this is part of
our roadmap.    
