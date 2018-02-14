package co.org.caferrerb.domotica.powerservice.rest;

import co.org.caferrerb.domotica.powerservice.dto.HistoricoResponseDTO;
import co.org.caferrerb.domotica.powerservice.dto.PowerRegistrationRequestDTO;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;


@RestController
@RequestMapping("/v1/medicion")
public class MedicionServiceRest {

        @RequestMapping(value = "/registrar",method = RequestMethod.POST)
        public ResponseEntity<?> registarMedicion(@RequestBody PowerRegistrationRequestDTO reg){

            return new ResponseEntity<>(HttpStatus.OK);
        }

        @RequestMapping(value = "/historico/{punto}/{fechainicio}/{fechafin}",method = RequestMethod.GET)
        public HistoricoResponseDTO consultarHistorico(@PathVariable(value = "punto")Long punto,
                                                       @PathVariable(value = "fechainicio")String fechainicio,
                                                       @PathVariable(value = "fechafin")String fechafin){
            return null;
        }


        @RequestMapping(value = "/ultimamedicion/{punto}",method = RequestMethod.GET)
        public Double ultimaMedicion(@PathVariable(value = "punto")Long punto){
            return null;
        }




}
