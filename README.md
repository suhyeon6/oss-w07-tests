# W07 Image Batch Testing
Course-written client and exercises using upstream stb (see vendor/stb/LICENSE).
Photo credit: assets/ATTRIBUTION.txt. No previous weekly files required.

Run inside Ubuntu (WSL or an existing Docker container):
    make
    mkdir -p output
    ./bin/image-lab "assets/day one.jpg" output/one.png gray
    bash scripts/batch.sh output/batch "assets/day one.jpg" assets/broken.jpg "assets/day two.jpg"

The batch script is the initial version to review. It always prints DONE and
returns 0, even if the image program rejects an input. The C program is provided.

Requirement: attempt every input; print DONE only for successful files; print
FAILED and the input path to stderr for failures; return 1 if any input fails,
otherwise 0. Usage/output-directory errors return 2. Existing output directories
are rejected. Inputs for the core task have distinct base names.

Read scripts/batch.sh, src/main.c (caller), include/filters.h and src/filters.c
(callee), then tests/test_batch.sh and Makefile. Change scripts/batch.sh and add
checks to tests/test_batch.sh. No variants or answer implementation is distributed.

make check runs the provided C unit test and initial Bash smoke test. Its initial
success covers valid inputs only. Add a test BEFORE accepting the mixed-input fix.
Open output PNG files in VS Code. A folder with a new name is needed for each manual
batch run. Tests isolate their outputs using mktemp and clean up only that directory.

.github/workflows/check.yml runs make check after push or pull_request.
For the CI exercise, push the reproducing test with the initial implementation,
inspect its failure, then commit and push the implementation fix. Compare the
two revisions and their Actions logs. Use a dedicated empty W07 repository and
the Git authentication configured for the course. Account/setup problems can
be followed through the instructor demonstration. No new assessment submission
is required by this exercise.
AI use and assessment policies are announced separately by the instructor.
