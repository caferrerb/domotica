package co.org.caferrerb.domotica.persistencia.modelo.entidades;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.io.Serializable;

@Entity
public class Dispositvo implements Serializable {

    @Id
    //@GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String nombre;

    private Double potenciaNominal;

    public Dispositvo() {
    }

    public Dispositvo(String nombre, Double potenciaNominal) {
        this.nombre = nombre;
        this.potenciaNominal = potenciaNominal;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public Double getPotenciaNominal() {
        return potenciaNominal;
    }

    public void setPotenciaNominal(Double potenciaNominal) {
        this.potenciaNominal = potenciaNominal;
    }
}
