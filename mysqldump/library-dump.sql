-- MySQL dump 10.16  Distrib 10.1.33-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: library
-- ------------------------------------------------------
-- Server version	10.1.33-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `authors`
--

DROP TABLE IF EXISTS `authors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `authors` (
  `id_author` int(11) NOT NULL,
  `name` varchar(20) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `surname` varchar(20) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `patronymic` varchar(20) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id_author`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `authors`
--

LOCK TABLES `authors` WRITE;
/*!40000 ALTER TABLE `authors` DISABLE KEYS */;
INSERT INTO `authors` VALUES (1,'Стивен','Хокинг',''),(2,'Роджер','Пенроуз',''),(3,'Абнер','Шимони',''),(4,'Йоганес','Роен',''),(5,'Билл','Брайсон',''),(6,'Митио','Каку',''),(7,'Карл','Циммер',''),(8,'Майкл','Аллаби',''),(9,'Роберт ','Хейзен',''),(10,'Ричард','Докинз',''),(11,'Джонатан','Смит','');
/*!40000 ALTER TABLE `authors` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `authors_of_the_book`
--

DROP TABLE IF EXISTS `authors_of_the_book`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `authors_of_the_book` (
  `isbn` int(12) DEFAULT NULL,
  `id_author` int(12) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `authors_of_the_book`
--

LOCK TABLES `authors_of_the_book` WRITE;
/*!40000 ALTER TABLE `authors_of_the_book` DISABLE KEYS */;
INSERT INTO `authors_of_the_book` VALUES (4236,1),(4236,2),(4236,3),(42367,4),(43367,5),(42368,6),(422167,7),(4236327,8),(4236753,9),(421672,10),(12367,11);
/*!40000 ALTER TABLE `authors_of_the_book` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `book`
--

DROP TABLE IF EXISTS `book`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `book` (
  `isbn` int(11) NOT NULL,
  `book_title` varchar(350) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `city_​​of_publication` varchar(20) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `number_of_pages` int(4) DEFAULT NULL,
  `year_of_publication` year(4) DEFAULT NULL,
  `price` int(7) DEFAULT NULL,
  `written_off` varchar(1) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`isbn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `book`
--

LOCK TABLES `book` WRITE;
/*!40000 ALTER TABLE `book` DISABLE KEYS */;
INSERT INTO `book` VALUES (4236,'Большое, малое и человеческий разум','Киев',234,2009,40,'t'),(12367,'Эгоистичный ген','Харьков',370,2011,70,'f'),(42367,'ББольшой атлас по анатомии','Киев',270,2011,30,'f'),(43367,'Краткая история почти всего на свете','Харьков',270,2011,30,'f'),(43368,'Гиперпространство. Научная одиссея через параллельные миры, дыры во времени и десятое измерение','Киев',270,2011,30,'f'),(421672,'Псевдонаука и паранормальные явления. Критический взгляд','Харьков',560,2011,90,'f'),(422167,'Микрокосм. E. coli и новая наука о жизни','Киев',430,2011,65,'f'),(4236327,'Земля. Иллюстрированный атлас','Житомир',230,2011,30,'f'),(4236753,'История Земли. От звездной пыли — к живой планете. Первые 4 500 000 000 лет','Харьков',280,2011,30,'t');
/*!40000 ALTER TABLE `book` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `books_of_reader`
--

DROP TABLE IF EXISTS `books_of_reader`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `books_of_reader` (
  `id_reader` int(12) DEFAULT NULL,
  `date_of_issue` date DEFAULT NULL,
  `date_of_return` date DEFAULT NULL,
  `is_buy` varchar(1) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `max_number_of_days` int(4) DEFAULT NULL,
  `isbn` int(12) DEFAULT NULL,
  `inventory_number` int(12) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `books_of_reader`
--

LOCK TABLES `books_of_reader` WRITE;
/*!40000 ALTER TABLE `books_of_reader` DISABLE KEYS */;
INSERT INTO `books_of_reader` VALUES (105,'2018-06-08',NULL,'f',80,12367,923),(107,'2018-03-08','2018-04-20','f',70,4236,1231),(107,'2018-06-08',NULL,'f',70,4236327,423),(107,'2017-08-20','2018-06-08','f',70,422167,133),(107,'2018-06-08',NULL,'f',25,43368,2213);
/*!40000 ALTER TABLE `books_of_reader` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `copies_of_books`
--

DROP TABLE IF EXISTS `copies_of_books`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `copies_of_books` (
  `inventory_number` int(11) NOT NULL,
  `isbn` int(7) DEFAULT NULL,
  `date_of_receiving` date DEFAULT NULL,
  `room` int(4) DEFAULT NULL,
  `shelf` int(3) DEFAULT NULL,
  `place` int(4) DEFAULT NULL,
  PRIMARY KEY (`inventory_number`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `copies_of_books`
--

LOCK TABLES `copies_of_books` WRITE;
/*!40000 ALTER TABLE `copies_of_books` DISABLE KEYS */;
INSERT INTO `copies_of_books` VALUES (123,4236,'2010-01-02',1,2,7),(133,422167,'2010-01-03',1,6,2),(323,42367,'2010-01-02',1,3,1),(423,4236327,'2010-01-03',1,7,1),(429,43367,'2010-01-02',1,4,2),(623,4236753,'2010-01-05',1,8,3),(823,421672,'2010-01-05',2,1,5),(923,12367,'2010-01-05',2,2,7),(1231,4236,'2010-01-02',1,2,8),(2213,43368,'2010-01-02',1,5,4);
/*!40000 ALTER TABLE `copies_of_books` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `genres_of_books`
--

DROP TABLE IF EXISTS `genres_of_books`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `genres_of_books` (
  `isbn` int(12) DEFAULT NULL,
  `id_genre` int(12) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `genres_of_books`
--

LOCK TABLES `genres_of_books` WRITE;
/*!40000 ALTER TABLE `genres_of_books` DISABLE KEYS */;
INSERT INTO `genres_of_books` VALUES (4236,327),(42367,327),(42367,128),(43367,327),(43368,327),(43368,328),(422167,327),(422167,129),(4236327,327),(4236753,327),(421672,327),(421672,328),(421672,129),(421672,131),(12367,327);
/*!40000 ALTER TABLE `genres_of_books` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `money`
--

DROP TABLE IF EXISTS `money`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `money` (
  `inventory_number` int(12) DEFAULT NULL,
  `сompensation_money` int(7) DEFAULT NULL,
  `fine_money` int(7) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `money`
--

LOCK TABLES `money` WRITE;
/*!40000 ALTER TABLE `money` DISABLE KEYS */;
INSERT INTO `money` VALUES (133,65,NULL);
/*!40000 ALTER TABLE `money` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `readers`
--

DROP TABLE IF EXISTS `readers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `readers` (
  `id_reader` int(11) NOT NULL,
  `mobile_phone` bigint(20) unsigned DEFAULT NULL,
  `home_phone` bigint(20) unsigned DEFAULT NULL,
  `date_of_birth` date DEFAULT NULL,
  `name` varchar(20) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `surname` varchar(20) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `patronymic` varchar(20) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id_reader`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `readers`
--

LOCK TABLES `readers` WRITE;
/*!40000 ALTER TABLE `readers` DISABLE KEYS */;
INSERT INTO `readers` VALUES (105,54868486972,234265425,'1995-04-07','КУЗЬМА','КОТРЕЛЕВ',''),(107,37257854699,435581,'1988-07-21','НИКОЛАЙ','ЕРЁМЕНКО','');
/*!40000 ALTER TABLE `readers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `thems`
--

DROP TABLE IF EXISTS `thems`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `thems` (
  `id_genre` int(12) DEFAULT NULL,
  `genre` varchar(25) COLLATE utf8mb4_unicode_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `thems`
--

LOCK TABLES `thems` WRITE;
/*!40000 ALTER TABLE `thems` DISABLE KEYS */;
INSERT INTO `thems` VALUES (327,'научная фантастика'),(328,'фентази'),(128,'география'),(129,'биология'),(130,'детектив'),(131,'роман');
/*!40000 ALTER TABLE `thems` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-06-23  9:48:51
