from openjdk:8-jdk-alpine
RUN apk update
RUN apk upgrade
RUN apk add bash

ARG NOMBRE_SERVICIO

ENV FOLDER_BIN /uservice/$NOMBRE_SERVICIO/bin
ENV FOLDER_CONF /uservice/$NOMBRE_SERVICIO/conf
ENV FOLDER_LOGS /uservice/$NOMBRE_SERVICIO/logs

ENV PROPERTIES_FILE application.properties


# crear carpetas--------------------

RUN mkdir  -p $FOLDER_BIN \
&&  mkdir  -p $FOLDER_CONF \
&&  mkdir  -p $FOLDER_LOGS

#dar permisos----------------------

COPY $PROPERTIES_FILE $FOLDER_CONF
COPY $NOMBRE_SERVICIO.jar $FOLDER_BIN

WORKDIR $FOLDER_BIN

#crear el sh de arranque.....
RUN echo java -jar -Dspring.config.location=file:$FOLDER_CONF/$PROPERTIES_FILE $NOMBRE_SERVICIO.jar > run.sh \
	&& chmod +x run.sh

ENTRYPOINT $FOLDER_BIN/run.sh







