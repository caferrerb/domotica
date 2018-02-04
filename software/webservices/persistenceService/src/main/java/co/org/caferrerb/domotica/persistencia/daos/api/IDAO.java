package co.org.caferrerb.domotica.persistencia.daos.api;

import co.org.caferrerb.domotica.persistencia.daos.util.PersisteceException;

import java.lang.reflect.ParameterizedType;
import java.util.List;

public interface IDAO<T,P> {

    default Class<T> getInstanceType(){

        return (Class<T>) ((ParameterizedType) getClass()
                .getGenericSuperclass()).getActualTypeArguments()[0];
    }


     T buscar(P pk) throws PersisteceException;
     List<T> listar() throws PersisteceException;
     void editar(T obj) throws PersisteceException;
     void crear(T obj)throws PersisteceException;
}
