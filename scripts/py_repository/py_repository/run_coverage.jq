def is_targeted_function(func):
  (0 < func.count) and
  (any(func.filenames[]; test(".*?base_lexer_gen\\.cpp$")) | not)
  ;

def filter_raw_json:
  {
    data: .data | map({
      functions: 
        .functions 
        | map(select(is_targeted_function(.)))
        | map({
            count,
            name,
            branches: .branches | map(select(0 < .[4])),
            filenames,
            regions: .regions | map(select(0 < .[2])),
          }),
      files: 
        .files 
        | map(
            . as $file 
            | select(
                (
                  ($file.filename | test("pb.(cc|h|cpp|hpp)$")) or
                  ($file.filename | contains("thirdparty"))
                )
                | not)) 
        | map({
            filename,
            summary,
            # Second element in segment list stores number of calls.
            segments: .segments | map(select(0 < .[2])), 
            # Branch call count is stored in 5th element
            branches: .branches | map(select(0 < .[4])),
            # expansions,
          }),
      totals,
    }),
    type, 
    version,
  };
