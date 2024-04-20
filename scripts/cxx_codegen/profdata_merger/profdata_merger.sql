
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
	FOREIGN KEY("Context") REFERENCES "CovContext" ("Id")
)

;