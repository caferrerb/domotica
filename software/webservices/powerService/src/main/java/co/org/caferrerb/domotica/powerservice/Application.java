package co.org.caferrerb.domotica.powerservice;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.cloud.client.circuitbreaker.EnableCircuitBreaker;
import org.springframework.cloud.netflix.hystrix.EnableHystrix;
import org.springframework.cloud.netflix.hystrix.dashboard.EnableHystrixDashboard;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;

//import org.springframework.boot.autoconfigure.



@Configuration
@ComponentScan(basePackages="co.org")
@EnableAutoConfiguration
@EnableJpaRepositories(basePackages="co.org")
@EntityScan(basePackages="co.org")
@EnableCircuitBreaker
@EnableHystrixDashboard

@EnableHystrix
//@EnableTurbine
public class Application {

    public static void main(String args[]){
        SpringApplication.run(Application.class, args);
    }
}
