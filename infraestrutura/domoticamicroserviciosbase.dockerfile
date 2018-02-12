#distribucion de linux para la infraestructura del microservicios.
FROM caferrerb/javamicroservicios

ARG NOMBRE_SERVICIO
ARG ARTIFACT_LOCATION


ENV HOME /home
ENV RUTABASERECETARIO "infraestrutura/recetas"
ENV RUTAREPOGIT https://github.com/caferrerb/domotica.git
ENV BRANCHGIT master
ENV PORT 8080

ENV RUTABASE $HOME/$NOMBRE_SERVICIO
ENV RUTALOGS $RUTABASE/logs
ENV RUTABIN $RUTABASE/bin
ENV RUTACOMPLETAGIT $RUTABASERECETARIO/$NOMBRE_SERVICIO


#crear estructura de carpetas para el microservicio
WORKDIR $HOME

#----descargar estructura de archivos desde el recetario en git--------------
RUN git init \
    && git config core.sparseCheckout true \
    && git remote add -f origin $RUTAREPOGIT \
    && echo $RUTABASERECETARIO"/"$NOMBRE_SERVICIO"/*" > .git/info/sparse-checkout \
    && git checkout $BRANCHGIT 

#organizar las carpetas....
RUN mv   $RUTACOMPLETAGIT $HOME \
    && rm -rf $RUTACOMPLETAGIT


#-------------------volumenes----------------------------------------------
VOLUME [ "$RUTALOGS" ]

#--------descargar de ejecutable--------------------------------------------
WORKDIR $RUTABIN
RUN wget -O $NOMBRE_SERVICIO.jar $ARTIFACT_LOCATION

EXPOSE $PORT
#-------executable--------------------------------------

ENTRYPOINT  [ $RUTABIN/runservice.sh ]


