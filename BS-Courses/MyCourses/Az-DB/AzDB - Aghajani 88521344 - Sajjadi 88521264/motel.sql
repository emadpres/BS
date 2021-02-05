-- phpMyAdmin SQL Dump
-- version 4.1.12
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: May 24, 2014 at 01:08 PM
-- Server version: 5.6.16
-- PHP Version: 5.5.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `motel`
--

DELIMITER $$
--
-- Procedures
--
CREATE DEFINER=`root`@`localhost` PROCEDURE `registerTransportation`(IN `code` INT, IN `roomNumber` INT, IN `destination` TEXT CHARSET utf8, IN `price` INT)
    MODIFIES SQL DATA
INSERT INTO transportation (code,roomNumber,destination,price) VALUES(code,roomNumber,destination,price)$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `reserve`(IN `fname` TEXT CHARSET utf8, IN `lname` TEXT CHARSET utf8, IN `tel` TEXT CHARSET utf8, IN `ID` TEXT CHARSET utf8, IN `sex` INT, IN `health` TEXT CHARSET utf8, IN `rNumber` INT, IN `startDate` DATE, IN `duration` INT, IN `staffID` INT)
    MODIFIES SQL DATA
BEGIN
	DECLARE ExistingUser INT(11);
	SET ExistingUser = (Select COUNT(*) from passenger 
                        WHERE passenger.ID = ID);
    
    IF ExistingUser > 0 THEN
        UPDATE passenger SET fname=fname, lname=lname,
        tel=tel, sex=sex , health=health 
        WHERE passenger.ID = ID;
    ELSE
        INSERT INTO passenger (fname,lname,tel,ID,sex,health)
   		VALUES (fname,lname,tel,ID, sex,health);
    END IF ;
        
	
    INSERT INTO reservation (roomNumber,passenger,startDate,duration,staff_ID)
    VALUE (rNumber,ID,startDate,duration,staffID);
    UPDATE rooms SET isFree=0
	WHERE roomNumber=rNumber;
END$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `event`
--

CREATE TABLE IF NOT EXISTS `event` (
  `type` int(11) NOT NULL DEFAULT '1',
  `tuzihat` text COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dumping data for table `event`
--

INSERT INTO `event` (`type`, `tuzihat`) VALUES
(1, 'ورود'),
(2, 'خروج');

-- --------------------------------------------------------

--
-- Table structure for table `passenger`
--

CREATE TABLE IF NOT EXISTS `passenger` (
  `fname` text COLLATE utf8_bin NOT NULL,
  `lname` text CHARACTER SET utf8 COLLATE utf8_persian_ci NOT NULL,
  `tel` text COLLATE utf8_bin NOT NULL,
  `ID` varchar(20) COLLATE utf8_bin NOT NULL DEFAULT '1234567890',
  `sex` int(11) NOT NULL,
  `health` text COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dumping data for table `passenger`
--

INSERT INTO `passenger` (`fname`, `lname`, `tel`, `ID`, `sex`, `health`) VALUES
('عماد', 'آقاجانی', '435', '11111111111', 0, 'سالم'),
('مریم', 'مرادی', '4499', '12', 1, 'سالم'),
('عماد', '11232', '123213', '1234', 0, 'سالم'),
('امیر', 'سجادی', '33', '90', 0, 'سالم'),
('ابراهیم', 'امامی', '11', '9999', 0, 'سالم');

-- --------------------------------------------------------

--
-- Table structure for table `reservation`
--

CREATE TABLE IF NOT EXISTS `reservation` (
  `roomNumber` int(11) NOT NULL,
  `passenger` varchar(20) COLLATE utf8_bin NOT NULL,
  `startDate` date NOT NULL DEFAULT '0000-00-00',
  `duration` int(11) NOT NULL,
  `staff_ID` int(11) NOT NULL,
  PRIMARY KEY (`roomNumber`,`startDate`),
  KEY `passenger` (`passenger`),
  KEY `staff_ID` (`staff_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dumping data for table `reservation`
--

INSERT INTO `reservation` (`roomNumber`, `passenger`, `startDate`, `duration`, `staff_ID`) VALUES
(1, '11111111111', '2014-05-24', 5, 1),
(2, '1234', '2010-05-24', 50, 2),
(2, '12', '2013-05-23', 20, 1),
(2, '9999', '2014-05-24', 10, 1),
(2, '1234', '2018-05-23', 5, 1),
(3, '1234', '2014-05-24', 5, 1),
(4, '1234', '2014-05-24', 5, 2),
(4, '90', '2014-05-25', 3, 1);

-- --------------------------------------------------------

--
-- Table structure for table `roomfree`
--

CREATE TABLE IF NOT EXISTS `roomfree` (
  `type` int(11) NOT NULL,
  `tuzihat` text COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dumping data for table `roomfree`
--

INSERT INTO `roomfree` (`type`, `tuzihat`) VALUES
(0, 'پر'),
(1, 'خالی');

-- --------------------------------------------------------

--
-- Table structure for table `rooms`
--

CREATE TABLE IF NOT EXISTS `rooms` (
  `roomNumber` int(11) NOT NULL,
  `type` int(11) NOT NULL DEFAULT '1',
  `isFree` int(11) NOT NULL DEFAULT '1',
  `status` text COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`roomNumber`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dumping data for table `rooms`
--

INSERT INTO `rooms` (`roomNumber`, `type`, `isFree`, `status`) VALUES
(1, 1, 0, ''),
(2, 1, 0, ' '),
(3, 2, 0, ''),
(4, 1, 0, ''),
(5, 2, 1, ''),
(6, 3, 1, ''),
(7, 3, 1, ''),
(8, 4, 1, ''),
(9, 1, 1, '');

-- --------------------------------------------------------

--
-- Table structure for table `staff`
--

CREATE TABLE IF NOT EXISTS `staff` (
  `staff_ID` int(11) NOT NULL AUTO_INCREMENT,
  `fname` text COLLATE utf16_bin NOT NULL,
  `lname` text COLLATE utf16_bin NOT NULL,
  `tel` int(11) NOT NULL,
  `ID` text COLLATE utf16_bin NOT NULL,
  `degree` text COLLATE utf16_bin NOT NULL,
  `xp` int(11) NOT NULL DEFAULT '1',
  `income` int(11) NOT NULL DEFAULT '750000',
  PRIMARY KEY (`staff_ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf16 COLLATE=utf16_bin AUTO_INCREMENT=3 ;

--
-- Dumping data for table `staff`
--

INSERT INTO `staff` (`staff_ID`, `fname`, `lname`, `tel`, `ID`, `degree`, `xp`, `income`) VALUES
(1, 'امیر', 'رضایی', 3432432, '210', 'لیسانس', 3, 850000),
(2, 'حانیه', 'مرکب', 912132132, '230', 'فوق لیسانس', 2, 1200000);

-- --------------------------------------------------------

--
-- Table structure for table `transportation`
--

CREATE TABLE IF NOT EXISTS `transportation` (
  `code` int(11) NOT NULL DEFAULT '0',
  `roomNumber` int(11) NOT NULL DEFAULT '1',
  `date` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `destination` text COLLATE utf8_bin NOT NULL,
  `price` int(11) NOT NULL DEFAULT '1000',
  PRIMARY KEY (`code`,`roomNumber`,`date`),
  KEY `roomNumber` (`roomNumber`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dumping data for table `transportation`
--

INSERT INTO `transportation` (`code`, `roomNumber`, `date`, `destination`, `price`) VALUES
(1122, 4, '2014-05-16 22:28:58', 'صص', 1000),
(1122, 5, '2014-05-16 21:54:59', 'تجریش', 1000),
(1122, 7, '2014-05-16 22:33:15', 'حسن', 1000),
(4455, 3, '2014-05-16 22:55:31', 'مم', 1000),
(4455, 3, '2014-05-17 16:38:57', 'تسیس', 1000),
(4455, 3, '2014-05-23 23:36:47', 'سس', 23213),
(4455, 3, '2014-05-24 13:20:40', 'شوش', 4500),
(4455, 5, '2014-05-24 13:53:00', 'asdas', 32423),
(4455, 8, '2014-05-23 23:37:38', 'تهرانسر', 9009);

-- --------------------------------------------------------

--
-- Table structure for table `transportation_agency`
--

CREATE TABLE IF NOT EXISTS `transportation_agency` (
  `code` int(11) NOT NULL,
  `name` text COLLATE utf8_bin,
  `address` text COLLATE utf8_bin,
  `tel` text COLLATE utf8_bin,
  PRIMARY KEY (`code`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dumping data for table `transportation_agency`
--

INSERT INTO `transportation_agency` (`code`, `name`, `address`, `tel`) VALUES
(1122, 'آزانس امیر', 'تهران - نرسیده به سعادت اباد', '02144889923'),
(4455, 'آزانس سعیدی', 'تهران', '02133906755');

-- --------------------------------------------------------

--
-- Table structure for table `work`
--

CREATE TABLE IF NOT EXISTS `work` (
  `staff_ID` int(11) NOT NULL,
  `type` int(11) NOT NULL DEFAULT '1',
  `time` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`staff_ID`,`type`,`time`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `work`
--

INSERT INTO `work` (`staff_ID`, `type`, `time`) VALUES
(1, 1, '2014-05-17 07:57:21'),
(1, 1, '2014-05-17 08:09:03'),
(1, 1, '2014-05-17 08:10:40'),
(1, 1, '2014-05-17 08:10:41'),
(1, 1, '2014-05-17 08:10:45'),
(1, 1, '2014-05-17 08:13:22'),
(1, 1, '2014-05-17 08:13:59'),
(1, 1, '2014-05-17 16:38:13'),
(1, 1, '2014-05-23 23:23:01'),
(1, 1, '2014-05-24 13:04:46'),
(1, 1, '2014-05-24 13:20:17'),
(1, 1, '2014-05-24 13:45:03'),
(1, 2, '2014-05-17 08:12:40'),
(1, 2, '2014-05-17 08:12:44'),
(1, 2, '2014-05-17 08:12:51'),
(1, 2, '2014-05-17 08:13:25'),
(1, 2, '2014-05-17 08:14:16'),
(2, 1, '2014-05-17 08:09:17'),
(2, 1, '2014-05-17 08:11:36'),
(2, 2, '2014-05-17 16:38:38'),
(2, 2, '2014-05-24 13:20:24');

--
-- Constraints for dumped tables
--

--
-- Constraints for table `reservation`
--
ALTER TABLE `reservation`
  ADD CONSTRAINT `reservation_ibfk_1` FOREIGN KEY (`roomNumber`) REFERENCES `rooms` (`roomNumber`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `reservation_ibfk_2` FOREIGN KEY (`passenger`) REFERENCES `passenger` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `reservation_ibfk_3` FOREIGN KEY (`staff_ID`) REFERENCES `staff` (`staff_ID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `transportation`
--
ALTER TABLE `transportation`
  ADD CONSTRAINT `transportation_ibfk_1` FOREIGN KEY (`code`) REFERENCES `transportation_agency` (`code`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `transportation_ibfk_2` FOREIGN KEY (`roomNumber`) REFERENCES `rooms` (`roomNumber`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `work`
--
ALTER TABLE `work`
  ADD CONSTRAINT `work_ibfk_1` FOREIGN KEY (`staff_ID`) REFERENCES `staff` (`staff_ID`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
