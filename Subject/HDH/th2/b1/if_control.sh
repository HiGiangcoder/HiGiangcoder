#!/bin/sh 
echo "Is it morning? Please answer yes or no" 
read timeofday 
#chú ý khoảng trắng trước sau [ và trước ]
if [ $timeofday = "yes" ]; then 
echo "Good morning" 
else 
echo "Good afternoon" 
fi 
exit 0 
