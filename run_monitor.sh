while [ 1 ] 
do 
	inotifywait -e modify cuterm 
	sleep 0.1
	xterm -geometry 100x50+2611+90 -e ./cuterm &
	pid=$!
	sleep 10
	kill -9 ${pid}
done
