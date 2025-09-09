# MPI Point-to-Point Communication Exercises

This repository contains a collection of small MPI programs demonstrating **point-to-point communication** with `MPI_Send`, `MPI_Recv`, `MPI_Bsend`, and related functions.  
Each file corresponds to a different task.

---

## 📂 Programs

### 1. `mpi_proc_sum_avg.cpp`
- **Task**: Each process receives several numbers.  
  - Even-ranked processes compute and print the **sum**.  
  - Odd-ranked processes compute and print the **average**.

---

### 2. `mpi_bsend_single_value.cpp`
- **Task**: Each worker process has one floating-point value.  
- **Method**:  
  - Workers send their value to process 0 using `MPI_Bsend`.  
  - Process 0 receives the values in **descending rank order**.

---

### 3. `mpi_bsend_array.cpp`
- **Task**: Each worker process has an integer array of arbitrary length.  
- **Method**:  
  - Workers send arrays to process 0 with `MPI_Bsend`.  
  - Process 0 uses `MPI_Probe` and `MPI_Get_count` to determine array size, then receives and prints the contents.

---

### 4. `mpi_send_broadcast.cpp`
- **Task**: Process 0 reads a number and sends it to all worker processes.  
- **Method**:  
  - Uses `MPI_Send` from process 0 to each worker.  
  - Workers receive and print the broadcasted value.

---

### 5. `mpi_bsend_reverse_order.cpp`
- **Task**: Process 0 has a set of numbers equal to the number of worker processes.  
- **Method**:  
  - Process 0 sends one number to each worker, but in **reverse rank order**, using `MPI_Bsend`.  
  - Workers receive and print their assigned number.

---

### 6. `mpi_send_variable_array.cpp`
- **Task**: Each worker process may have an integer array of variable size.  
- **Method**:  
  - Workers send their arrays to process 0 using `MPI_Send`.  
  - Process 0 uses `MPI_Probe` and `MPI_Get_count` to determine array sizes and prints the received data along with the sender rank.

---

### 7. `mpi_probe_sum_values.cpp`
- **Task**: Each worker may hold a number.  
- **Method**:  
  - Workers send positive numbers to process 0.  
  - Process 0 uses `MPI_Probe` and `MPI_Recv` to collect exactly *k* numbers and compute their **sum**:contentReference[oaicite:0]{index=0}.

---

### 8. `mpi_ring_pass.cpp`
- **Task**: Pass a value around all processes in a **ring topology**.  
- **Method**:  
  - Process 0 sends an integer to process 1.  
  - Each process prints, modifies, and forwards the value.  
  - The last process sends it back to process 0.  
  - Uses synchronous sends (`MPI_Ssend`):contentReference[oaicite:1]{index=1}.

---

### 9. `mpi_pack_gather.cpp`
- **Task**: Each process (except rank 0) sends a double and part of an integer array.  
- **Method**:  
  - Workers pack data into a buffer with `MPI_Pack`.  
  - Data is gathered at process 0 with `MPI_Gather`.  
  - Process 0 unpacks data using `MPI_Unpack` and prints results:contentReference[oaicite:2]{index=2}.

---

### 10. `mpi_send_to_target.cpp`
- **Task**: One process is chosen as target `N`.  
- **Method**:  
  - All other processes send a double to process `N`.  
  - Process `N` prints its own value.  
  - Every process prints the number and the sender rank it received from:contentReference[oaicite:3]{index=3}.

---

### 11. `mpi_chain_exchange.cpp`
- **Task**: Exchange values in a **chain of processes**.  
- **Method**:  
  - Each process reads an integer and sends it forward.  
  - Another process receives, sends back, and prints the returned value.  
  - Demonstrates sequential send/recv pattern:contentReference[oaicite:4]{index=4}.

---

### 12. `mpi_sendrecv_swap.cpp`
- **Task**: Processes exchange values with their “mirror rank” (`size - rank - 1`).  
- **Method**:  
  - Uses `MPI_Sendrecv_replace` to swap doubles between pairs.  
  - Each process prints the received value:contentReference[oaicite:5]{index=5}.

---

### 13. `mpi_tagged_messages.cpp`
- **Task**: Workers send numbers to process 0 with different **tags**.  
- **Method**:  
  - Each worker reads pairs `(value, tag)` and sends to process 0.  
  - Process 0 uses `MPI_Recv` with varying tags and prints the values.  
  - Demonstrates selective reception by tags:contentReference[oaicite:6]{index=6}.

---
### 14. `mpi_scatterv_variable.cpp`
- **Task**: Scatter a variable number of integers from process 0 to all processes.  
- **Method**:  
  - Process 0 prepares counts (`cnt`) and displacements (`dis`) of different lengths.  
  - Uses `MPI_Scatterv` to distribute segments of varying size to each process.  
- **Concept**: Custom distribution with `MPI_Scatterv`:contentReference[oaicite:0]{index=0}.

---

### 15. `mpi_scatterv_fixed_blocks.cpp`
- **Task**: Scatter groups of 3 doubles from process 0 to all processes.  
- **Method**:  
  - Process 0 sets uniform block sizes (`3`) and offsets.  
  - Calls `MPI_Scatterv` to send 3 doubles to each process.  
- **Concept**: Scatter fixed-size blocks with offsets:contentReference[oaicite:1]{index=1}.

---

### 16. `mpi_alltoallv_example.cpp`
- **Task**: Exchange data among all processes with variable displacements.  
- **Method**:  
  - Each process has 2 doubles to send.  
  - Uses `MPI_Alltoallv` with per-process displacements to exchange data.  
- **Concept**: All-to-all communication with different data offsets:contentReference[oaicite:2]{index=2}.

---

### 17. `mpi_scatterv_packed.cpp`
- **Task**: Scatter packed data (int, double, int) from process 0 to all workers.  
- **Method**:  
  - Process 0 packs triples `(int, double, int)` into a buffer.  
  - Calls `MPI_Scatterv` with `MPI_PACKED`.  
  - Workers unpack and print received triples.  
- **Concept**: Using `MPI_Pack` / `MPI_Unpack` with `MPI_Scatterv`:contentReference[oaicite:3]{index=3}.

---

### 18. `mpi_gather_packed.cpp`
- **Task**: Gather packed data from workers into process 0.  
- **Method**:  
  - Workers pack a double and several integers into a buffer.  
  - `MPI_Gather` collects them at process 0.  
  - Process 0 unpacks values and prints results.  
- **Concept**: Gathering structured data with packing:contentReference[oaicite:4]{index=4}.

---

### 19. `mpi_type_resized_rows.cpp`
- **Task**: Collect rows of a matrix using custom datatypes.  
- **Method**:  
  - Each worker sends an array of doubles.  
  - Process 0 defines a **resized datatype** to receive rows directly into a 2D array.  
- **Concept**: Creating a resized MPI datatype to align rows:contentReference[oaicite:5]{index=5}.

---

### 20. `mpi_type_vector_blocks.cpp`
- **Task**: Collect square sub-blocks from workers into process 0.  
- **Method**:  
  - Workers send `N×N` blocks of integers.  
  - Process 0 defines a **vector datatype** with stride to place blocks into a larger array.  
- **Concept**: Using `MPI_Type_vector` for block placement:contentReference[oaicite:6]{index=6}.

---

### 21. `mpi_type_indexed_lower_triangle.cpp`
- **Task**: Send lower-triangular parts of matrices to workers.  
- **Method**:  
  - Process 0 defines an **indexed datatype** with varying block lengths/displacements.  
  - Sends lower-triangle sections to workers.  
  - Workers receive and print them.  
- **Concept**: Using `MPI_Type_indexed` to describe irregular data layouts:contentReference[oaicite:7]{index=7}.

---

### 22. `mpi_type_indexed_custom.cpp`
- **Task**: Receive irregular blocks of integers from workers with tags.  
- **Method**:  
  - Workers send arrays with a specific tag.  
  - Process 0 probes messages, builds a custom **indexed datatype** with displacements, and receives data.  
  - Final array assembled and printed.  
- **Concept**: Advanced usage of `MPI_Type_indexed` with tags:contentReference[oaicite:8]{index=8}.
  
---

### 23. `mpi_reduce_scatter_min.cpp`
- **Task**: Perform a reduce-scatter with operation **MIN**.  
- **Method**:  
  - Process 0 prepares an array of integers.  
  - `MPI_Reduce_scatter` distributes results so that rank *i* gets `i+2` elements.  
- **Concept**: Using `MPI_Reduce_scatter` with variable counts .

---

### 24. `mpi_group_even_scatter.cpp`
- **Task**: Work only with even-ranked processes.  
- **Method**:  
  - Create a group of even ranks with `MPI_Group_incl`.  
  - Build a new communicator and scatter integers from process 0.  
  - Even ranks receive and print values.  
- **Concept**: Creating subgroups of processes:contentReference[oaicite:0]{index=0}.

---

### 25. `mpi_group_excl_allgather.cpp`
- **Task**: Exclude even ranks from a communicator and gather data.  
- **Method**:  
  - Use `MPI_Group_excl` to remove even ranks.  
  - Odd ranks gather their double pairs with `MPI_Allgather`.  
- **Concept**: Building communicators by excluding ranks:contentReference[oaicite:1]{index=1}.

---

### 26. `mpi_comm_split_gather.cpp`
- **Task**: Split communicator based on a flag, then gather.  
- **Method**:  
  - Processes with `N == 1` form a new communicator.  
  - Each such process contributes a double.  
  - Gather at the last rank of the new communicator.  
- **Concept**: Using `MPI_Comm_split` + `MPI_Gather`:contentReference[oaicite:2]{index=2}.

---

### 27. `mpi_comm_split_allgather.cpp`
- **Task**: Split communicator and perform **Allgather**.  
- **Method**:  
  - Processes with `N == 1` join a new communicator.  
  - They all gather doubles with `MPI_Allgather` and print results.  
- **Concept**: Communicator splitting + collective allgather:contentReference[oaicite:3]{index=3}.

---

### 28. `mpi_comm_split_allreduce.cpp`
- **Task**: Split communicator and compute sum with **Allreduce**.  
- **Method**:  
  - Processes with `N == 1` join a new communicator.  
  - Their values are summed with `MPI_Allreduce`.  
- **Concept**: Communicator splitting + collective allreduce:contentReference[oaicite:4]{index=4}.

---

### 29. `mpi_cartesian_2d_coords.cpp`
- **Task**: Create a 2D Cartesian communicator.  
- **Method**:  
  - Process 0 reads grid dimension `n`.  
  - Calls `MPI_Cart_create` with dimensions `{n, size/n}`.  
  - Processes output their coordinates.  
- **Concept**: Mapping ranks to Cartesian grid coordinates:contentReference[oaicite:5]{index=5}.

---

### 30. `mpi_cartesian_3d_gather.cpp`
- **Task**: Create a 3D Cartesian communicator and gather values along rows.  
- **Method**:  
  - Dimensions `{2, 2, size/4}`.  
  - Sub-communicators are created with `MPI_Cart_sub`.  
  - Gather integers along the third dimension.  
- **Concept**: Cartesian topology + subcommunicators:contentReference[oaicite:6]{index=6}.

---

### 31. `mpi_cartesian_split_reduce_bcast.cpp`
- **Task**: Split a 3D Cartesian communicator into 2D slices.  
- **Method**:  
  - `MPI_Comm_split` groups processes by z-coordinate.  
  - Perform `MPI_Reduce` to compute sum in each slice.  
  - Then broadcast the result within each slice.  
- **Concept**: Combining Cartesian topology with reduce + broadcast:contentReference[oaicite:7]{index=7}.

---

### 32. `mpi_cartesian_rank_lookup.cpp`
- **Task**: Find Cartesian rank from coordinates.  
- **Method**:  
  - Create a 2D Cartesian communicator with dimensions `{M, N}`.  
  - Processes read coordinates `(X, Y)`.  
  - Use `MPI_Cart_rank` to map coordinates to rank.  
  - If invalid, output `-1`.  
- **Concept**: Cartesian mapping and error handling:contentReference[oaicite:8]{index=8}.

---
### 33. `mpi_cartesian_shift_chain.cpp`
- **Task**: Create a 1D Cartesian communicator and shift values.  
- **Method**:  
  - `MPI_Cart_create` builds a 1D topology of size = number of processes.  
  - `MPI_Cart_shift` determines source and destination ranks.  
  - All non-zero ranks send a double to the previous neighbor.  
  - All non-last ranks receive from the next neighbor and print the value.  
- **Concept**: Chain communication using `MPI_Cart_shift` .

---

### 34. `mpi_cartesian_3d_shift.cpp`
- **Task**: Create a 3D Cartesian communicator and exchange values along z-axis.  
- **Method**:  
  - Dimensions = `{2, 2, size/4}`, with periodicity in the z-direction.  
  - Processes send and receive using `MPI_Cart_shift` along axis 2.  
  - `MPI_Sendrecv_replace` is used for in-place exchange.  
- **Concept**: Shifting values in 3D Cartesian topology:contentReference[oaicite:0]{index=0}.

---

### 35. `mpi_graph_neighbors_exchange.cpp`
- **Task**: Create a custom **graph communicator** and exchange integers with neighbors.  
- **Method**:  
  - `MPI_Graph_create` builds a graph from adjacency lists.  
  - Each process queries its neighbors with `MPI_Graph_neighbors_count`.  
  - Sends a value to each neighbor and receives back their value.  
  - Outputs all results.  
- **Concept**: Communication based on custom graph topology:contentReference[oaicite:1]{index=1}.

---

### 36. `mpi_graph_custom_topology.cpp`
- **Task**: Construct a more complex custom graph topology and exchange values.  
- **Method**:  
  - `edges` and `index` arrays define irregular neighbor connections.  
  - `MPI_Graph_create` builds communicator with those connections.  
  - Each process sends its integer to all neighbors with `MPI_Sendrecv`.  
  - Collects and prints all received values.  
- **Concept**: Using `MPI_Graph_create` to define arbitrary topologies:contentReference[oaicite:2]{index=2}.

## 🛠 Tech Stack
- **Language**: C++  
- **Library**: MPI (Message Passing Interface)  
- **Concepts**: Point-to-point communication, buffered sends, probes, dynamic message sizes.

---

## 🚀 How to Run
Compile with `mpic++`:
```bash
mpic++ mpi_proc_sum_avg.cpp -o mpi_proc_sum_avg
