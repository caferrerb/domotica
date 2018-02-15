from openjdk:8-jdk-alpine

ARG NOMBRE_SERVICIO
ARG RUTA_FOLDER_CONF
ARG RUTA_FILE_JAR

ENV FOLDER_BIN /service/$NOMBRE_SERVICIO/bin
ENV FOLDER_CONF /service/$NOMBRE_SERVICIO/conf
ENV FOLDER_LOGS /service/$NOMBRE_SERVICIO/logs


# crear carpetas--------------------
RUN mkdir /service \
	&& mkdir /service/$NOMBRE_SERVICIO \   
	&& mkdir  $FOLDER_BIN \
	&& mkdir  $FOLDER_CONF \
	&& mkdir  $FOLDER_LOGS

#dar permisos----------------------

RUN echo $RUTA_FOLDER_CONF

COPY $RUTA_FOLDER_CONF $FOLDER_CONF
COPY $RUTA_FILE_JAR $FOLDER_CONF

WORKDIR $FOLDER_BIN
ENTRYPOINT java -jar -Dspring.config.location=file:../conf/application.properties $NOMBRE_SERVICIO.jar







