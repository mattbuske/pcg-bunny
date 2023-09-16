# Release Notes

{%- macro release_header(release='v0.0.0',release_date='(01/01/1970)',name_space='mattbuske/pcg-bunny') %}
## <a href="https://github.com/{{ name_space }}/releases/tag/{{ release }}" target="_blank" title="{{ release }} Release" alt="{{ release }} Release">**{{ release }} {{ release_date }}**</a>
{% endmacro -%}

{{ release_header('v1.2.0','(09/15/2023)') }}
- Improved documentation
- Restructured documentation to fit the Standard MkDocs structure
- Updated documentation to address new warnings from MkDocs 1.5+
- Updated python packages in requirements.txt
- Updated Github publish action to newest version
- Restructured folders to reflect the different languages this project is implemented in
- Updated License file to remove file extension
- Removed License file from generated documentation
- Recreated the project in C#
- Added Dependabot to Github Actions
- Bumped versions in requirements.txt

{{ release_header('v1.1.4','(03/05/2023)') }}
- Improved documentation
- Upgraded MkDocs dependencies
- Simplified Dockerfiles
- Deleted the "dist" folder and build executables.

{{ release_header('v1.1.3','(01/29/2023)') }}
- Added MIT License
- Added Code Of Conduct
- Added contributing guidelines
- Expanded on documentation
- Expanded upon Readme file
- Updated documentation icon
- Improved Docker-Compose file to use ${PWD} for more flexible paths
- Enhanced Dockerfile for better clarity, reduced image size and increased security
- Optimized Alpine Dockerfile for easier copying and simplified run command.
- Revamped Github Actions to enhance the dynamic nature of document build.

{{ release_header('v1.1.2','(10/25/2022)') }}
- Expanded on documentation

{{ release_header('v1.1.1','(10/24/2022)') }}
- Added documentation and workflow tools

{{ release_header('v1.1.0','(04/19/2022)') }}
- Fixed spelling error in code
- Included binary in release
- Moved source files to a separate directory
- Added changelog, readme, and documentation
- Included files for building and deploying the project

{{ release_header('v1.0.1','(02/26/2017)') }}
- Created the project repository

{{ release_header('v1.0.0','(02/2014)') }}
- Initial release