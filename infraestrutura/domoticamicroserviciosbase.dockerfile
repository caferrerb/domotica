#distribucion de linux para la infraestructura del microservicios.
FROM caferrerb/javamicroservicios

ENV NOMBRE_SERVICIO ""
ENV ARTIFACT_LOCATION ""


ENV HOME /home
ENV RUTABASERECETARIO "infraestrutura/recetas"
ENV RUTAREPOGIT https://github.com/caferrerb/domotica.git
ENV BRANCHGIT master
ENV PORT 8080

ENV RUTABASE $HOME/$NOMBRE_SERVICIO
ENV RUTALOGS $RUTABASE/logs
ENV RUTABIN $RUTABASE/bin
ENV RUTACOMPLETAGIT $RUTABASERECETARIO/$NOMBRE_SERVICIO


VOLUME [ "$RUTALOGS" ]

COPY downloaddeploy.sh /
RUN ["chmod", "+x", "/downloaddeploy.sh"]
ENTRYPOINT /downloaddeploy.sh $NOMBRE_SERVICIO $ARTIFACT_LOCATION $RUTAREPOGIT $BRANCHGIT $HOME


