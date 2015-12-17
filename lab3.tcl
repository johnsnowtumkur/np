 set ns [new Simulator]
set tf [open lab3a.tr w]
$ns trace-all $tf
set nf [open lab3a.nam w]
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

$n0 label "Source/FTP"
$n1 label "Source/Telnet"
$n3 label "Destination/FTP"
$n5 label "Desination/Telnet"

$ns color 1 "red"
$ns color 2 "orange"

$ns duplex-link $n0 $n2 100Mb 1ms DropTail
$ns duplex-link $n1 $n2 100Mb 1ms DropTail
$ns duplex-link $n2 $n3 100Mb 1ms DropTail
$ns duplex-link $n2 $n4 100Mb 1ms DropTail
$ns duplex-link $n4 $n5 100Mb 1ms DropTail

set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
set sink3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink3

set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1
set telnet1 [new Application/Telnet]
$telnet1 attach-agent $tcp1
set sink5 [new Agent/TCPSink]
$ns attach-agent $n5 $sink5

$telnet1 set packetSize_ 1000Mb
$telnet1 set interval_ 0.00001


$ns connect $tcp0 $sink3
$ns connect $tcp1 $sink5


$tcp0 set class_ 1
$tcp1 set class_ 2

proc finish { } {
	global ns nf tf
	$ns flush-trace
	exec nam lab3a.nam &
	close $nf
	close $tf
	exit 0
}

$ns at 0.1 "$ftp0 start"
$ns at 0.1 "$telnet1 start"
$ns at 15 "finish"
$ns run
