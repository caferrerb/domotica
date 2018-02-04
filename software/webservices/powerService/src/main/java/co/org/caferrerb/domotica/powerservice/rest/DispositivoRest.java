package co.org.caferrerb.domotica.powerservice.rest;

import co.org.caferrerb.domotica.persistencia.modelo.entidades.Dispositvo;
import co.org.caferrerb.domotica.powerservice.servicios.DispositivoService;
import com.netflix.hystrix.HystrixCommand;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/v1/dispositivo")
public class DispositivoRest {

    @Autowired
    private DispositivoService dispService;

    @RequestMapping(value = "/crear",method = RequestMethod.POST)
    public void crear(@RequestBody Dispositvo disp){
        dispService.crear(disp);
    }

    @RequestMapping(value = "/listar",method = RequestMethod.GET)
    public List<Dispositvo> listar(){
        return dispService.listar();
    }


    @RequestMapping(value = "/buscar/{id}",method = RequestMethod.GET)
    public ResponseEntity<?> buscar(@PathVariable(value = "id") Long id){
        Dispositvo disp= dispService.buscar(id);
        if(disp!=null){
            return new ResponseEntity<Dispositvo>(disp,HttpStatus.OK);
        }else{
            return new ResponseEntity<Dispositvo>(HttpStatus.NOT_FOUND);
        }
    }




}
