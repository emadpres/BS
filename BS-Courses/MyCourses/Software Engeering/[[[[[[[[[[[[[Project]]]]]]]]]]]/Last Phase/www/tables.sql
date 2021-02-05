-- phpMyAdmin SQL Dump
-- version 3.1.3
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jul 06, 2012 at 08:30 PM
-- Server version: 5.1.32
-- PHP Version: 5.2.9-1

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `se`
--

-- --------------------------------------------------------

--
-- Table structure for table `ekhterat`
--

DROP TABLE IF EXISTS `ekhterat`;
CREATE TABLE IF NOT EXISTS `ekhterat` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `name` varchar(200) COLLATE utf8_unicode_ci NOT NULL,
  `memo` text COLLATE utf8_unicode_ci,
  `point` int(11) NOT NULL DEFAULT '0',
  `moaref` varchar(32) COLLATE utf8_unicode_ci DEFAULT NULL,
  `reg_id` varchar(32) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name_2` (`name`),
  KEY `user_id` (`user_id`),
  KEY `name` (`name`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=13 ;

--
-- Dumping data for table `ekhterat`
--

INSERT INTO `ekhterat` (`id`, `user_id`, `name`, `memo`, `point`, `moaref`, `reg_id`) VALUES
(6, 1, 'doogh', '', 0, NULL, NULL),
(10, 2, 'ali', 'kjkdghskfhsdkj', 0, NULL, NULL),
(11, 2, 'Ø³Ù„Ø§Ù…', '131321564564', 0, NULL, ''),
(12, 2, 'sadsadasddasasd', 'asddassad', 0, NULL, 'adsadasdasd');

-- --------------------------------------------------------

--
-- Table structure for table `moaref`
--

DROP TABLE IF EXISTS `moaref`;
CREATE TABLE IF NOT EXISTS `moaref` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(20) DEFAULT NULL,
  `name` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `family` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `gerayesh` varchar(320) COLLATE utf8_unicode_ci DEFAULT NULL,
  `post` varchar(320) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=2 ;

--
-- Dumping data for table `moaref`
--

INSERT INTO `moaref` (`id`, `user_id`, `name`, `family`, `gerayesh`, `post`) VALUES
(1, 2, 'fssdffsd', 'fsdfsd', 'fdsfds', 'fsdfsddfs');

-- --------------------------------------------------------

--
-- Table structure for table `moteghazi`
--

DROP TABLE IF EXISTS `moteghazi`;
CREATE TABLE IF NOT EXISTS `moteghazi` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `password` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `Email` varchar(100) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=10 ;

--
-- Dumping data for table `moteghazi`
--

INSERT INTO `moteghazi` (`id`, `username`, `password`, `Email`) VALUES
(1, 'hasan', 'fc3f318fba8b3c1502bece62a27712df', 'a@a.a'),
(2, 'ali', '86318e52f5ed4801abe1d13d509443de', 'aa.aa.a');

--
-- Constraints for dumped tables
--

--
-- Constraints for table `ekhterat`
--
ALTER TABLE `ekhterat`
  ADD CONSTRAINT `ekhterat_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `moteghazi` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
