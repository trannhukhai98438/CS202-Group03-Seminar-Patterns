# CS202 Group 03 — Design Patterns Seminar

This repository contains the seminar materials produced by Group 03 for **CS202 — Programming Systems**. The project studies three behavioral design patterns in modern C++:

- Chain of Responsibility
- Iterator
- Visitor

The repository includes academic reports written in LaTeX, C++ implementations, Visitor benchmark source code, seminar presentations, contribution records, change records, and group-level AI usage documentation.

## Project Links

- **GitHub repository:** [CS202-Group03-Seminar-Patterns](https://github.com/trannhukhai98438/CS202-Group03-Seminar-Patterns)
- **Canva presentation:** [Visitor Pattern](https://canva.link/jxvxk72gq4woaf2)
- **AI-redesigned presentation:**[AI slides](https://canva.link/d4tgud1mtuh5wxy)
- ** Contribution spreadsheet:** [Contribution](https://docs.google.com/spreadsheets/d/1ZbmAaIeLaS9DHWmoXCLgWsuYlQ_nApl3fGz3P6p5rtE/edit?usp=sharing)

## Repository Structure

```text
CS202-Group03-Seminar-Patterns/
├── AI_Usage/
│   ├── AI_Chat_Log.md
│   └── AI_Usage_Declaration.md
├── Changes/
│   └── Change.md
├── Contribution/
│   └── Group03.xlsx
├── Reports/
│   ├── ChainofResponsibility_report/
│   │   ├── main.tex
│   │   ├── Contents/
│   │   ├── Figures/
│   │   ├── General/
│   │   └── ref/
│   ├── Iterator_report/
│   │   ├── main.tex
│   │   ├── Contents/
│   │   ├── Figures/
│   │   ├── General/
│   │   └── ref/
│   └── Visitor_report/
│       ├── main.tex
│       ├── Appendix/
│       ├── Contents/
│       ├── Figures/
│       ├── General/
│       └── ref/
├── Seminar_Presentation/
│   ├── Visitor Pattern - Original Design.pdf
│   └── Visitor Pattern - Modern AI Redesign.pdf
├── Src_Code/
│   ├── ChainOfResponsibility_Pattern/
│   │   └── ChainofResponsibility.cpp
│   ├── Iterator_Pattern/
│   │   └── Iterator.cpp
│   └── Visitor_Pattern/
│       ├── ClassicVisitor.cpp
│       ├── ModernVisitor.cpp
│       ├── AcyclicVisitor.cpp
│       └── Benchmark/
│           ├── BenchmarkSupport.h
│           ├── ClassicBenchmark.cpp
│           ├── ModernBenchmark.cpp
│           └── AcyclicBenchmark.cpp
├── .gitignore
└── README.md
```

## Reports and Source Code

| Pattern | LaTeX report | C++ source |
|---|---|---|
| Chain of Responsibility | [Report](Reports/ChainofResponsibility_report) | [Source](Src_Code/ChainOfResponsibility_Pattern/ChainofResponsibility.cpp) |
| Iterator | [Report](Reports/Iterator_report) | [Source](Src_Code/Iterator_Pattern/Iterator.cpp) |
| Visitor | [Report](Reports/Visitor_report) | [Source and benchmarks](Src_Code/Visitor_Pattern) |

Each report is organized as an independent LaTeX project with its own `main.tex`, content files, figures, settings, and bibliography.

## Seminar Presentation

The submitted Visitor presentation is available in two versions:

- [Original design](Seminar_Presentation/Visitor%20Pattern%20-%20Original%20Design.pdf)
- [Modern AI redesign](Seminar_Presentation/Visitor%20Pattern%20-%20Modern%20AI%20Redesign.pdf)

The redesigned presentation was produced from the original material with the intention of preserving the academic content, C++ code, UML diagrams, slide order, and quiz answers while modernizing the visual layout.

## AI Usage Documentation

The finalized group-level AI disclosure documents are available here:

- [AI Usage Declaration](AI_Usage/AI_Usage_Declaration.md)
- [AI Chat Log](AI_Usage/AI_Chat_Log.md)

These documents describe the AI-assisted tasks reported by each member, the significant recorded interactions, how generated material was reviewed, and the responsibility retained by the group members.

## Contribution and Change Records

- [Member contribution spreadsheet](Contribution/Group03.xlsx)
- [Project change log](Changes/Change.md)

## Compiling a Report

To compile a report locally, enter the corresponding report directory and compile its `main.tex`. For example:

```sh
cd Reports/Visitor_report
pdflatex main.tex
bibtex main
pdflatex main.tex
pdflatex main.tex
```

On Overleaf, upload the contents of one report directory as a separate project and select its `main.tex` as the main document.

## Group Members

| Full Name | Student ID |
|---|---:|
| Đỗ Viết Hoàng Long | 25125024 |
| Trần Như Khải | 25125045 |
| Trần Đăng Khoa | 25125056 |
| Trần Minh Khoa | 25125057 |

## Academic Information

- **Course:** CS202 — Programming Systems
- **Program:** Advanced Program in Computer Science (APCS)
- **University:** University of Science, Vietnam National University Ho Chi Minh City
- **Supervisors:**
  - PhD. DINH Ba Tien
  - MSc. TRUONG Phuoc Loc
  - MSc. HO Tuan Thanh
