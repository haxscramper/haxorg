
CREATE TABLE "CovFunction" (
	id INTEGER NOT NULL, 
	mangled VARCHAR NOT NULL, 
	demangled VARCHAR NOT NULL, 
	parsed JSON, 
	PRIMARY KEY (id)
)

