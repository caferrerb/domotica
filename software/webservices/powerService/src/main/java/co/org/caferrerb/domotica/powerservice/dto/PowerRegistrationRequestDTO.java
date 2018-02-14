package co.org.caferrerb.domotica.powerservice.dto;

import java.util.Date;

public class PowerRegistrationRequestDTO {

    private Long idPunto;

    private Long idDisposivito;

    private Double medicion;

    private Date fecha;

    public PowerRegistrationRequestDTO() {
    }

    public PowerRegistrationRequestDTO(Long idPunto, Long idDisposivito, Double medicion) {
        this.idPunto = idPunto;
        this.idDisposivito = idDisposivito;
        this.medicion = medicion;
        fecha=new Date();
    }

    public Long getIdPunto() {
        return idPunto;
    }

    public void setIdPunto(Long idPunto) {
        this.idPunto = idPunto;
    }

    public Long getIdDisposivito() {
        return idDisposivito;
    }

    public void setIdDisposivito(Long idDisposivito) {
        this.idDisposivito = idDisposivito;
    }

    public Double getMedicion() {
        return medicion;
    }

    public void setMedicion(Double medicion) {
        this.medicion = medicion;
    }
}
