#!/bin/sh -e

while read line
do
  name=`echo $line | awk '{print $1}'`
  url=`echo $line | awk '{print $2}'`
  
  if [ ! -f $name ]
  then
    wget --continue --no-check-certificate --output-document=$name $url
  fi
  
done < sources.txt