#!/bin/sh -e

while read line
do
  name=`echo $line | awk '{print $1}'`
  url=`echo $line | awk '{print $2}'`
  
  set -x
  test ! -f $name
  wget --continue --no-check-certificate --output-document=$name $url
  set +x
  
done < sources.txt