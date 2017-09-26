cmake_minimum_required(VERSION 3.7)
include(~/Documents/HermitCore/cmake/HermitCore-Application.cmake)

project(Lighttpd C)

include(CheckCSourceCompiles)
include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckSymbolExists)
include(CheckVariableExists)
include(CheckTypeSize)
include(CheckLibraryExists)
include(CMakeDetermineCCompiler)
include(FindThreads)
include(FindPkgConfig)

set(COMMON_SRC
	base64.c buffer.c log.c
	keyvalue.c chunk.c
	http_chunk.c stream.c fdevent.c
	stat_cache.c plugin.c joblist.c etag.c array.c
	data_string.c data_array.c
	data_integer.c md5.c data_fastcgi.c
	vector.c
	fdevent_select.c fdevent_libev.c
	fdevent_poll.c fdevent_linux_sysepoll.c
	fdevent_solaris_devpoll.c fdevent_solaris_port.c
	fdevent_freebsd_kqueue.c
	data_config.c
	inet_ntop_cache.c crc32.c
	connections-glue.c
	configfile-glue.c
	http-header-glue.c
	http_auth.c
	splaytree.c
	rand.c
	status_counter.c safe_memclear.c
)

add_executable(lighttpd
	server.c
	response.c
	connections.c
	network.c
	network_darwin_sendfile.c
	network_freebsd_sendfile.c
	network_linux_sendfile.c
	network_openssl.c
	network_solaris_sendfilev.c
	network_write.c
	network_write_mmap.c
	network_write_no_mmap.c
	network_writev.c
	configfile.c
	configparser.c
	request.c
	proc_open.c
	${COMMON_SRC}
)

