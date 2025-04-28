mkdir _build
cd _build
cmake -DGNSS_RECEIVER_BUILD_EXAMPLES=ON ../
cd ..
copy ".\exampleData\FrameParserExampleSignal.txt" ".\_build\examples\FrameParserExample"
copy ".\exampleData\AbsoluteShiftEstimationExampleSignal.txt" ".\_build\examples\AbsoluteShiftEstimationExample"