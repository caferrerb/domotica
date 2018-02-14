package co.org.caferrerb.domotica.powerservice.dto;

import java.util.Date;
import java.util.List;

public class HistoricoResponseDTO {

    private Date fechaInicio;
    private Date fechaFin;
    private int punto;
    private List<MedidaResponseDTO> medidas;

    public HistoricoResponseDTO() {
    }


    public HistoricoResponseDTO(Date fechaInicio, Date fechaFin, int punto, List<MedidaResponseDTO> medidas) {
        this.fechaInicio = fechaInicio;
        this.fechaFin = fechaFin;
        this.punto = punto;
        this.medidas = medidas;
    }

    public Date getFechaInicio() {
        return fechaInicio;
    }

    public void setFechaInicio(Date fechaInicio) {
        this.fechaInicio = fechaInicio;
    }

    public Date getFechaFin() {
        return fechaFin;
    }

    public void setFechaFin(Date fechaFin) {
        this.fechaFin = fechaFin;
    }

    public int getPunto() {
        return punto;
    }

    public void setPunto(int punto) {
        this.punto = punto;
    }

    public List<MedidaResponseDTO> getMedidas() {
        return medidas;
    }

    public void setMedidas(List<MedidaResponseDTO> medidas) {
        this.medidas = medidas;
    }


    public static class MedidaResponseDTO {

        private Date fecha;
        private Double medicion;

        public MedidaResponseDTO() {
        }

        public MedidaResponseDTO(Date fecha, Double medicion) {
            this.fecha = fecha;
            this.medicion = medicion;
        }

        public Date getFecha() {
            return fecha;
        }

        public void setFecha(Date fecha) {
            this.fecha = fecha;
        }

        public Double getMedicion() {
            return medicion;
        }

        public void setMedicion(Double medicion) {
            this.medicion = medicion;
        }
    }
}
