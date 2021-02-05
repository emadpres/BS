USE [master]
GO

/****** Object:  Database [School]    Script Date: 05/13/2012 12:55:34 ******/
CREATE DATABASE [School] ON  PRIMARY 
( NAME = N'School', FILENAME = N'C:\Program Files (x86)\Microsoft SQL Server\MSSQL.2\MSSQL\DATA\School.mdf' , SIZE = 3072KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'School_log', FILENAME = N'C:\Program Files (x86)\Microsoft SQL Server\MSSQL.2\MSSQL\DATA\School_log.ldf' , SIZE = 1024KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO

ALTER DATABASE [School] SET COMPATIBILITY_LEVEL = 90
GO

IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [School].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO

ALTER DATABASE [School] SET ANSI_NULL_DEFAULT OFF 
GO

ALTER DATABASE [School] SET ANSI_NULLS OFF 
GO

ALTER DATABASE [School] SET ANSI_PADDING OFF 
GO

ALTER DATABASE [School] SET ANSI_WARNINGS OFF 
GO

ALTER DATABASE [School] SET ARITHABORT OFF 
GO

ALTER DATABASE [School] SET AUTO_CLOSE OFF 
GO

ALTER DATABASE [School] SET AUTO_CREATE_STATISTICS ON 
GO

ALTER DATABASE [School] SET AUTO_SHRINK OFF 
GO

ALTER DATABASE [School] SET AUTO_UPDATE_STATISTICS ON 
GO

ALTER DATABASE [School] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO

ALTER DATABASE [School] SET CURSOR_DEFAULT  GLOBAL 
GO

ALTER DATABASE [School] SET CONCAT_NULL_YIELDS_NULL OFF 
GO

ALTER DATABASE [School] SET NUMERIC_ROUNDABORT OFF 
GO

ALTER DATABASE [School] SET QUOTED_IDENTIFIER OFF 
GO

ALTER DATABASE [School] SET RECURSIVE_TRIGGERS OFF 
GO

ALTER DATABASE [School] SET  DISABLE_BROKER 
GO

ALTER DATABASE [School] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO

ALTER DATABASE [School] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO

ALTER DATABASE [School] SET TRUSTWORTHY OFF 
GO

ALTER DATABASE [School] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO

ALTER DATABASE [School] SET PARAMETERIZATION SIMPLE 
GO

ALTER DATABASE [School] SET READ_COMMITTED_SNAPSHOT OFF 
GO

ALTER DATABASE [School] SET  READ_WRITE 
GO

ALTER DATABASE [School] SET RECOVERY SIMPLE 
GO

ALTER DATABASE [School] SET  MULTI_USER 
GO

ALTER DATABASE [School] SET PAGE_VERIFY CHECKSUM  
GO

ALTER DATABASE [School] SET DB_CHAINING OFF 
GO

