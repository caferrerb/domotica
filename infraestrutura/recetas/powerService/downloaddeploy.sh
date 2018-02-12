#!/bin/sh


NOMBRE_SERVICIO=$1

RUTAREPOGIT=https://github.com/caferrerb/domotica.git
BRANCHGIT=master
RUTABASERECETARIO=infraestrutura/recetas
HOME=/Users/caferrerb/Desktop/folder
RUTACOMPLETAGIT=$HOME/$RUTABASERECETARIO

RUTABASE=$HOME/$NOMBRE_SERVICIO
RUTALOGS=$RUTABASE/logs
RUTABIN=$RUTABASE/bin

rm -rf $HOME
mkdir $HOME

cd $HOME

git init 
git config core.sparseCheckout true
git remote add -f origin $RUTAREPOGIT 
echo $RUTABASERECETARIO"/"$NOMBRE_SERVICIO"/*" > .git/info/sparse-checkout
git checkout $BRANCHGIT 

cp  -r $RUTACOMPLETAGIT/$NOMBRE_SERVICIO $HOME/$NOMBRE_SERVICIO
rm -rf $RUTACOMPLETAGIT
rm -rf $HOME/.git
rm $HOME/infraestrutura
