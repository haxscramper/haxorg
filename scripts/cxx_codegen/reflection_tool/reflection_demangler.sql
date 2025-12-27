CREATE TABLE "BinarySymbol" (
  "Id" INTEGER NOT NULL, 
  "Name" VARCHAR NOT NULL,
  "Demangled" VARCHAR NOT NULL,
  "DemangledHeadId" INTEGER NOT NULL, 
  "Size" INTEGER NOT NULL,
  "Address" INTEGER NOT NULL,
  "Section" INTEGER NOT NULL, 
  PRIMARY KEY("Id"),
  FOREIGN KEY("DemangledHeadId") REFERENCES "DemangledHead" ("Id"),
  FOREIGN KEY("Section") REFERENCES "BinarySection" ("Id")
)
;

CREATE TABLE "DemangledHead" (
  "Id" INTEGER NOT NULL, 
  "Kind" INTEGER NOT NULL,
  "Fields" JSON,
  PRIMARY KEY ("Id")
)
;

CREATE TABLE "DemangledNested" (
  "ComponentIndex" INTEGER NOT NULL,
  "Parent" INTEGER NOT NULL,
  "Self" INTEGER,
  FOREIGN KEY ("Parent") REFERENCES "DemangledHead" ("Id"),
  FOREIGN KEY ("Self") REFERENCES "DemangledHead" ("Id")
)
;

CREATE TABLE "BinarySection" (
  "Id" INTEGER NOT NULL, 
  "Name" VARCHAR NOT NULL,
  PRIMARY KEY ("Id")
)
;
