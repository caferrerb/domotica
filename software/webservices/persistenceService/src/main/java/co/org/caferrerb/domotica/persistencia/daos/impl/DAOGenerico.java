package co.org.caferrerb.domotica.persistencia.daos.impl;

import co.org.caferrerb.domotica.persistencia.daos.api.IDAO;
import co.org.caferrerb.domotica.persistencia.daos.util.PersisteceException;
import org.springframework.beans.factory.annotation.Autowired;

import javax.persistence.EntityManager;
import javax.persistence.Query;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import java.util.List;

public class DAOGenerico<T,P> implements IDAO<T,P> {

    @Autowired
    private EntityManager em;



    @Override
    public T buscar(P pk) throws PersisteceException {
        return em.find(getInstanceType(),pk);
    }

    @Override
    public List<T> listar() throws PersisteceException {

        Class<T> clase=getInstanceType();
        CriteriaBuilder cb=em.getCriteriaBuilder();
        CriteriaQuery<T> cq=cb.createQuery(clase);
        Root<T> root=cq.from(clase);
        cq.select(root);

        Query q=em.createQuery(cq);

        return q.getResultList();
    }

    @Override
    public void editar(T obj) throws PersisteceException {
        em.merge(obj);
    }

    @Override
    public void crear(T obj) throws PersisteceException {
        em.persist(obj);
    }
}
