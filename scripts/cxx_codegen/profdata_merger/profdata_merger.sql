
CREATE TABLE "CovFunction" (
	id INTEGER NOT NULL, 
	mangled VARCHAR NOT NULL, 
	demangled VARCHAR NOT NULL, 
	parsed JSON, 
	PRIMARY KEY (id)
)

;

CREATE TABLE "CovContext" (
	id INTEGER NOT NULL, 
	name VARCHAR NOT NULL, 
	parent VARCHAR, 
	profile VARCHAR NOT NULL, 
	params JSON, 
	binary VARCHAR NOT NULL, 
	PRIMARY KEY (id)
)

;