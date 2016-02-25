SELECT
    QcTrack.Md5Sum,
    QcTrack.FilePath,
    Assembly.Name AS Assembly,
    QcTrack.Assay,
    QcTrack.AssayCategory,
    QcTrack.CellType,
    QcTrack.CellTypeCategory,
    QcTrack.ReleasingGroup,
    QcTrack.Institution
FROM QcTrack 
INNER JOIN Assembly
ON QcTrack.AssemblyId = Assembly.AssemblyId;