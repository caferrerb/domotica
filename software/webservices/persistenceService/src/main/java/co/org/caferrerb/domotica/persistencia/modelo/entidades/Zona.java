package co.org.caferrerb.domotica.persistencia.modelo.entidades;

import javax.persistence.Entity;
import javax.persistence.Id;
import java.io.Serializable;

@Entity
public class Zona implements Serializable {

    @Id
    private Long numeroZona;

    private String nombre;

    public Zona() {
    }

    public Zona(Long numeroZona, String nombre) {
        this.numeroZona = numeroZona;
        this.nombre = nombre;
    }

    public Long getNumeroZona() {
        return numeroZona;
    }

    public void setNumeroZona(Long numeroZona) {
        this.numeroZona = numeroZona;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }
}
