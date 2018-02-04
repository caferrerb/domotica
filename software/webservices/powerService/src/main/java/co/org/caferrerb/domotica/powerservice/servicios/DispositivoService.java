package co.org.caferrerb.domotica.powerservice.servicios;


import co.org.caferrerb.domotica.persistencia.daos.api.IDAODispositivo;
import co.org.caferrerb.domotica.persistencia.modelo.entidades.Dispositvo;

import com.netflix.hystrix.contrib.javanica.annotation.HystrixCommand;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

@Service
public class DispositivoService {

    @Autowired
    private IDAODispositivo daoDisp;

    public void crear(Dispositvo disp){
        daoDisp.save(disp);
    }

    public Dispositvo buscar(Long id){
        return daoDisp.findOne(id);
    }

    @HystrixCommand(fallbackMethod ="listarTemp" )
    public List<Dispositvo> listar(){
        if(Math.random()>0.5) {
            List<Dispositvo> res = new ArrayList<>();
            daoDisp.findAll().forEach(res::add);
            return res;
        }else{
            throw  new RuntimeException();
        }
    }
    public List<Dispositvo> listarTemp(){
        return new ArrayList<>();
    }

}
