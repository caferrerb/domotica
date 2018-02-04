package co.org.caferrerb.domotica.persistencia.modelo.entidades;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Date;

@Entity
public class ConsumoDispositivo implements Serializable {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Temporal(TemporalType.TIMESTAMP)
    private Date tiempoRegistro;

    private Double medicion;

    @ManyToOne
    @JoinColumns({
            @JoinColumn(name = "idzona",referencedColumnName = "idzona"),
            @JoinColumn(name = "numeroPunto",referencedColumnName = "numeropunto"),
    })
    private UbicacionDispositivo ubicacionDispositivo;


    public ConsumoDispositivo() {
    }

    public ConsumoDispositivo(Double medicion,UbicacionDispositivo ubicacionDispositivo) {
        this.medicion = medicion;
        this.ubicacionDispositivo=ubicacionDispositivo;
        tiempoRegistro=new Date();
    }

    public ConsumoDispositivo(Date tiempoRegistro, Double medicion,UbicacionDispositivo ubicacionDispositivo) {
        this.tiempoRegistro = tiempoRegistro;
        this.medicion = medicion;
        this.ubicacionDispositivo=ubicacionDispositivo;

    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Date getTiempoRegistro() {
        return tiempoRegistro;
    }

    public void setTiempoRegistro(Date tiempoRegistro) {
        this.tiempoRegistro = tiempoRegistro;
    }

    public Double getMedicion() {
        return medicion;
    }

    public void setMedicion(Double medicion) {
        this.medicion = medicion;
    }

    public UbicacionDispositivo getUbicacionDispositivo() {
        return ubicacionDispositivo;
    }

    public void setUbicacionDispositivo(UbicacionDispositivo ubicacionDispositivo) {
        this.ubicacionDispositivo = ubicacionDispositivo;
    }
}
