# Search Engine Project

Collaborators: Emilio Munoz, Tiffany Nguyen


## Overview
The `supersearch` program is a custom search engine built to index and query a large collection of financial news articles. It uses an AVL tree-based inverted index to handle documents and metadata efficiently.

### Key Features
- **Interactive User Interface:** Create indices, perform queries, and manage indices.
- **Advanced Queries:** Supports operators like `ORG:` and `PERSON:` for filtering results based on metadata.
- **Relevance Ranking:** Uses term frequency-inverse document frequency (tf-idf) and metadata for ranking results.
- **Persistence:** Saves indices to disk for reuse across sessions.

---

## Installation and Setup

### Prerequisites
Ensure the following dependencies are installed:
- **C++ Compiler:** GCC or Clang (supporting C++17 or later).
- **JSON Parser:** The project uses [RapidJSON](https://rapidjson.org/), which is included in the template.

### Dataset
- Download the dataset: [US Financial News Articles](https://www.kaggle.com/jeet2016/us-financial-news-articles).
- The dataset contains over 300,000 articles in JSON format. Use the dataset for indexing and testing the program.

---

## How to Run

1. **Locate the Executable**  
   The `supersearch` executable is precompiled and located in the `build` directory.

2. **Navigate to the Build Directory**  
   Open a terminal and run:
   ```bash
   cd /path/to/Project4wvdatastructures\ copy/build

3. **Run the program**
   Execute the supersearch program:
   ./supersearch


   
