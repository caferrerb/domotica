#!/bin/sh

VERSION_ARTIFACT=1.0-SNAPSHOT

NOMBRE_SERVICIO=$1
ARTIFACT_LOCATION=https://oss.sonatype.org/content/repositories/snapshots/com/github/caferrerb/domotica/$NOMBRE_SERVICIO/$VERSION_ARTIFACT/

HOME=/Users/caferrerb/Desktop/folder

RUTABASE=$HOME/$NOMBRE_SERVICIO
RUTALOGS=$RUTABASE/logs
RUTABIN=$RUTABASE/bin


mkdir $RUTABIN/temp
cd $RUTABIN/temp
wget -r -l 1 $ARTIFACT_LOCATION