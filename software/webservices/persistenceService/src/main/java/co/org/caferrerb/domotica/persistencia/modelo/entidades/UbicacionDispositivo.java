package co.org.caferrerb.domotica.persistencia.modelo.entidades;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@IdClass(UbicacionDispositivo.UbicacionDispositivoPK.class)
public class UbicacionDispositivo implements Serializable {



    public static class UbicacionDispositivoPK implements  Serializable{
        private Long zona;
        private Integer numeroPunto;

        public UbicacionDispositivoPK() {
        }

        public UbicacionDispositivoPK(Long zona, Integer numeroPunto) {
            this.zona = zona;
            this.numeroPunto = numeroPunto;
        }

        public Long getZona() {
            return zona;
        }

        public void setZona(Long zona) {
            this.zona = zona;
        }

        public Integer getNumeroPunto() {
            return numeroPunto;
        }

        public void setNumeroPunto(Integer numeroPunto) {
            this.numeroPunto = numeroPunto;
        }
    }

    @Id
    @ManyToOne
    @JoinColumn(name = "idzona")
    private Zona zona;

    @Id
    @Column(name = "numeropunto")
    private Integer numeroPunto;


    public UbicacionDispositivo() {
    }

    public UbicacionDispositivo(Zona zona, Integer numeroPunto) {
        this.zona = zona;
        this.numeroPunto = numeroPunto;
    }

    public Zona getZona() {
        return zona;
    }

    public void setZona(Zona zona) {
        this.zona = zona;
    }

    public Integer getNumeroPunto() {
        return numeroPunto;
    }

    public void setNumeroPunto(Integer numeroPunto) {
        this.numeroPunto = numeroPunto;
    }
}
