\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{etoys-guide}[2011/12/10 v0.1 Modified article class for EToys guides, created by Severin Lemaignan]

% Passes and class options to the underlying article class
%\DeclareOption*{\PassOptionsToClass{\CurrentOption}{article}}
%\ProcessOptions

% Load LaTeX's article class with default configuration
\LoadClass[a4paper,12pt]{article}


\RequirePackage{fullpage}
\RequirePackage{sectsty}

\RequirePackage{fancyhdr} %headers and footers
\pagestyle{fancy}

\RequirePackage[utf8]{inputenc}

\RequirePackage[T1]{fontenc}
\pdfmapfile{+ubuntu-regular.map}
\pdfmapfile{+ubuntu-it.map}
\pdfmapfile{+ubuntu-bold.map}
\renewcommand{\rmdefault}{Ubuntu}

% Set default font to scriptsize and sans-serif for margin notes
\let\myMargin\marginpar
\renewcommand{\marginpar}[1]{\myMargin{{\scriptsize \sffamily #1}}}


%################# Header and footer with fancyhdr
\headheight=14.85pt
% Section section name in lower case
%\renewcommand{\chaptermark}[1]{\markboth{#1}{}} %only when doc type = book
%\renewcommand{\sectionmark}[1]{\markright{#1}}

\fancyhf{}
\fancyhead[RO,LE]{\scriptsize\bfseries\leftmark}
%\fancyhead[LE]{\rightmark}
\fancyfoot[LE,RO]{\bfseries\thepage}
\renewcommand{\headrulewidth}{0.3pt}
%\addtolength{\headheight}{2pt}
\addtolength{\headsep}{20pt}
\addtolength{\footskip}{10pt}
\renewcommand{\footrulewidth}{0pt}
\fancypagestyle{plain}{\fancyhead{}\renewcommand{\headrulewidth}{0pt}}
