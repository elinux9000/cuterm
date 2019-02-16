run_at_startup=1
FILES_TO_MONITOR="*.c *.h"
while [ 1 ] 
do 
	if [ $run_at_startup ] ; then
		unset run_at_startup
	else
	inotifywait -e modify $FILES_TO_MONITOR
	sleep 0.1
	fi 
	clear
	cscope -b
	make 
	if [ $? -eq 0 ]; then
		xterm -geometry 100x50+2611+90 -e ./cuterm &
		pid=$!
		sleep 10
		kill ${pid}
	fi
done
