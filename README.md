
CREATE DATABASE IF NOT EXISTS BoardingPassDB;
USE BoardingPassDB;

-- Desactivar las comprobaciones de claves foráneas
SET FOREIGN_KEY_CHECKS = 0;

-- Eliminar tablas existentes si existen
DROP TABLE IF EXISTS Vuelos;
DROP TABLE IF EXISTS Aerodou;
DROP TABLE IF EXISTS Pasajeros;

-- Activar las comprobaciones de claves foráneas
SET FOREIGN_KEY_CHECKS = 1;

-- Crear tabla de Pasajeros
CREATE TABLE IF NOT EXISTS Pasajeros (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre_completo VARCHAR(255) NOT NULL
);

-- Crear tabla de Aerodou (Aeropuertos)
CREATE TABLE IF NOT EXISTS Aerodou (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(255) NOT NULL,
    codigo VARCHAR(10) NOT NULL
);

-- Crear tabla de Vuelos
CREATE TABLE IF NOT EXISTS Vuelos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    numero_vuelo VARCHAR(10) NOT NULL,
    aerodou_id INT,
    FOREIGN KEY (aerodou_id) REFERENCES Aerodou(id)
);
