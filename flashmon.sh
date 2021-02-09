#!/bin/sh
pio run -t upload
if [ $? -ne 0 ]; then
echo "ERROR building"
exit 1
fi
sleep 2
pio device monitor --raw
