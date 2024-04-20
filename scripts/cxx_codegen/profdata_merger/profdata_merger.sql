
CREATE TABLE "CovFunction" (
	"Id" INTEGER NOT NULL, 
	"Mangled" VARCHAR NOT NULL, 
	"Demangled" VARCHAR NOT NULL, 
	"Parsed" JSON, 
	PRIMARY KEY ("Id")
)

;

CREATE TABLE "CovContext" (
	"Id" INTEGER NOT NULL, 
	"Name" VARCHAR NOT NULL, 
	"Parent" VARCHAR, 
	"Profile" VARCHAR NOT NULL, 
	"Params" JSON, 
	"Binary" VARCHAR NOT NULL, 
	PRIMARY KEY ("Id")
)

;

CREATE TABLE "CovRegion" (
	"Id" INTEGER NOT NULL, 
	"Function" INTEGER NOT NULL, 
	"Context" INTEGER NOT NULL, 
	"IsBranch" BOOLEAN NOT NULL, 
	"ExecutionCount" INTEGER NOT NULL, 
	"FalseExecutionCount" INTEGER NOT NULL, 
	"Folded" BOOLEAN NOT NULL, 
	"FileId" INTEGER NOT NULL, 
	"ExpandedFileId" INTEGER NOT NULL, 
	"LineStart" INTEGER NOT NULL, 
	"ColumnStart" INTEGER NOT NULL, 
	"LineEnd" INTEGER NOT NULL, 
	"ColumnEnd" INTEGER NOT NULL, 
	"RegionKind" VARCHAR(15), 
	PRIMARY KEY ("Id"), 
	FOREIGN KEY("Function") REFERENCES "CovFunction" ("Id"), 
	FOREIGN KEY("Context") REFERENCES "CovContext" ("Id"), 
	FOREIGN KEY("FileId") REFERENCES "CovFile" ("Id"), 
	FOREIGN KEY("ExpandedFileId") REFERENCES "CovFile" ("Id")
)

;

CREATE TABLE "CovFile" (
	"Id" INTEGER NOT NULL, 
	"Path" VARCHAR NOT NULL, 
	PRIMARY KEY ("Id")
)

;

CREATE TABLE "CovInstantiationGroup" (
	"Id" INTEGER NOT NULL, 
	"Line" INTEGER NOT NULL, 
	"Col" INTEGER NOT NULL, 
	PRIMARY KEY ("Id")
)

;

CREATE TABLE "CovFunctionInstantiation" (
	"Id" INTEGER NOT NULL, 
	"Instantiation" INTEGER NOT NULL, 
	"Function" INTEGER NOT NULL, 
	PRIMARY KEY ("Id"), 
	FOREIGN KEY("Instantiation") REFERENCES "CovInstantiationGroup" ("Id"), 
	FOREIGN KEY("Function") REFERENCES "CovFunction" ("Id")
)

;

CREATE TABLE "CovSegment" (
	"Id" INTEGER NOT NULL, 
	"Line" INTEGER NOT NULL, 
	"Col" INTEGER NOT NULL, 
	"Count" INTEGER NOT NULL, 
	"HasCount" BOOLEAN NOT NULL, 
	"IsRegionEntry" BOOLEAN NOT NULL, 
	"IsGapRegion" BOOLEAN NOT NULL, 
	"File" INTEGER NOT NULL, 
	"Context" INTEGER NOT NULL, 
	"SegmentIndex" INTEGER NOT NULL, 
	PRIMARY KEY ("Id"), 
	FOREIGN KEY("File") REFERENCES "CovFile" ("Id"), 
	FOREIGN KEY("Context") REFERENCES "CovContext" ("Id")
)

;