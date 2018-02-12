#!/bin/sh

#$NOMBRE_SERVICIO $ARTIFACT_LOCATION $RUTAREPOGIT $BRANCHGIT $RUTABASERECETARIO $HOME

NOMBRE_SERVICIO=$1
ARTIFACT_LOCATION=$2

RUTAREPOGIT=$3 #https://github.com/caferrerb/domotica.git
BRANCHGIT=$4 #master
RUTABASERECETARIO=$5 #infraestrutura/recetas
HOME=$6 #/Users/caferrerb/Desktop/folder
RUTACOMPLETAGIT=$HOME/$RUTABASERECETARIO

RUTABASE=$HOME/$NOMBRE_SERVICIO
RUTALOGS=$RUTABASE/logs
RUTABIN=$RUTABASE/bin

rm -rf $RUTABASE
mkdir $RUTABASE

cd $HOME

git init 
git config core.sparseCheckout true
git remote add -f origin $RUTAREPOGIT 
echo $RUTABASERECETARIO"/"$NOMBRE_SERVICIO"/*" > .git/info/sparse-checkout
git checkout $BRANCHGIT 

cp  -r $RUTACOMPLETAGIT/$NOMBRE_SERVICIO $RUTABASE
rm -rf $RUTACOMPLETAGIT
rm -rf $HOME/.git
rm $HOME/infraestrutura

cd $RUTABASE

sh configdeploy.sh $NOMBRE_SERVICIO $ARTIFACT_LOCATION $HOME

