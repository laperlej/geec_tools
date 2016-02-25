CREATE TABLE Assembly
(
AssemblyId integer NOT NULL,
Name text NOT NULL,
Species text NOT NULL,
CONSTRAINT PK_Assembly PRIMARY KEY (AssemblyId)
);

CREATE TABLE ChromSize
(
ChromSizeId integer NOT NULL,
Name text NOT NULL,
FilePath text,
AssemblyId text NOT NULL,
CONSTRAINT PK_ChromSize PRIMARY KEY (ChromSizeId),
CONSTRAINT FK_ChromSize_Assembly FOREIGN KEY (AssemblyId) REFERENCES Assembly(AssemblyId)
);

CREATE TABLE QcTrack
(
QcTrackId integer NOT NULL,
Md5Sum text NOT NULL,
FilePath text,
AssemblyId text NOT NULL,
Assay text,
AssayCategory text,
CellType text,
CellTypeCategory text,
ReleasingGroup text,
Institution text,
CONSTRAINT PK_QcTrack PRIMARY KEY (QcTrackId),
CONSTRAINT UQ_QcTrack_Md5Sum UNIQUE (Md5Sum),
CONSTRAINT FK_QcTrack_Assembly FOREIGN KEY(AssemblyId) REFERENCES Assembly(AssemblyId)
);

CREATE TABLE Hdf5Group
(
Hdf5GroupId integer NOT NULL,
QcTrackId integer NOT NULL,
Hdf5FileId integer,
BinSize integer NOT NULL,
ChromSizeId integer,
CONSTRAINT PK_Hdf5Group PRIMARY KEY (Hdf5GroupId),
CONSTRAINT FK_Hdf5Group_QcTrack FOREIGN KEY (QcTrackId) REFERENCES QcTrack(QcTrackId),
CONSTRAINT FK_Hdf5Group_Hdf5File FOREIGN KEY (Hdf5FileId) REFERENCES Hdf5File(Hdf5FileId),
CONSTRAINT FK_Hdf5Group_ChromSize FOREIGN KEY (ChromSizeId) REFERENCES ChromSize(ChromSizeId)
);

CREATE TABLE ZscoreGroup
(
ZscoreGroupId integer NOT NULL,
Hdf5GroupId integer,
ZscoreFileId integer,
InclusionId integer,
ExclusionId integer,
CONSTRAINT PK_ZscoreGroup PRIMARY KEY (ZscoreGroupId),
CONSTRAINT FK_ZscoreGroup_Hdf5Group FOREIGN KEY (Hdf5GroupId) REFERENCES Hdf5Group(Hdf5GroupId),
CONSTRAINT FK_ZscoreGroup_ZscoreFile FOREIGN KEY (ZscoreFileId) REFERENCES ZscoreFile(ZscoreFileId),
CONSTRAINT FK_ZscoreGroup_Region1 FOREIGN KEY (InclusionId) REFERENCES Region(RegionId),
CONSTRAINT FK_ZscoreGroup_Region2 FOREIGN KEY (ExclusionId) REFERENCES Region(RegionId)
);

CREATE TABLE CorrelationFile
(
CorrelationFileId integer NOT NULL,
FilePath text,
CONSTRAINT PK_CorrelationFile PRIMARY KEY (CorrelationFileId)
);

CREATE TABLE MatrixFile
(
MatrixFileId integer NOT NULL,
FilePath text,
CONSTRAINT PK_MatrixFile PRIMARY KEY (MatrixFileId)
);

CREATE TABLE ZscoreFile
(
ZscoreFileId integer NOT NULL,
FilePath text,
CONSTRAINT PK_ZscoreFile PRIMARY KEY (ZscoreFileId)
);

CREATE TABLE Hdf5File
(
Hdf5FileId integer NOT NULL,
FilePath text,
CONSTRAINT PK_Hdf5File PRIMARY KEY (Hdf5FileId)
);

CREATE TABLE Region
(
RegionId integer,
AssemblyId text,
FilePath text,
CONSTRAINT PK_Region PRIMARY KEY (RegionId),
CONSTRAINT FK_Region_Assembly FOREIGN KEY (AssemblyId) REFERENCES Assembly(AssemblyId)
);
