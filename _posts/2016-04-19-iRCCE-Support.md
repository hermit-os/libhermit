---
layout:     post
title:      iRCCE support
author:     Stefan Lankes
tags: 	    ircce message-passing bare-metal video numa
subtitle:   Running Message-Passing Applications in a bare-metal environment
---

The video shows message-passing applications running in bare-metal environment.
All application based on the message passing library <a href="http://www.lfbs.rwth-aachen.de/publications/files/iRCCE.pdf">iRCCE</a>.

In this demo, NUMA nodes are isolated and on each node runs a HermitCore instance.
This promises a reduction of remote memory accesses, which increases the scalability of the system.

<div style="width:100%; margin:0; auto" align="center">
<script type="text/javascript" src="https://asciinema.org/a/1nwbnhi957hxpmet1zsxcoyg5.js" id="asciicast-1nwbnhi957hxpmet1zsxcoyg5" async=""></script>
</div>
