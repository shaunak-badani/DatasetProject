# Brownian particle trajectories dataset 

### Executive summary
    The dataset describes a set of trajectories for a brownian particle in a harmonic potential whose center also moves with time.
    The inspiration for this dataset comes from the paper ["Machine learning the thermodynamic arrow of time"](https://www.nature.com/articles/s41567-020-1018-2).

    The problem we're trying to solve is determining the arrow of time from a given time-series data of the particle in motion. Given a trajectory, can I determine if it is a forward trajectory (state A to state B), or if it is a backward trajectory (state B to state A)?

![Image](./images/Visual_representation.png)

    This dataset, once generated, could be used for a variety of different analyses, such as understanding the Crook's Fluctuation theorem. The methods to generate the dataset, along with the dataset, can give the necessary tools for someone interested to work on this problem with little to no domain knowledge of molecular dynamics and statistical mechanics.


### Description of data

    There are `1003` columns in this dataset.
    The first 1001 columns denote the position of the particle - ith column denotes position of the particle at timestep i. 
    The next two columns are `w`, the work done in moving the particle from the start position to the end position, and `isForward`, denoting if the trajectory is a forward trajectory or a backward trajectory.

| Column Name     | Description           | 
| ------------- |:-------------:| 
| x_i    | Denotes the position of the particle at timestep `i`. |
| w      | Work done in moving the particle from the start position to the end position.      |
| isForward | Denotes if the trajectory is a forward trajectory or a backward trajectory.     | 

### How to run data generation script

```bash
g++ Dataset_generation.cpp -o brownian_gen
./brownian_gen
```

### Power analysis results

Power analysis was conducted on a graph denoting the histograms of forward and backward trajectories.

$$
\begin{align}
    M_1 &\approx 2.5 \\        
    M_2 &\approx -2.5 \\
    3 * \sigma &\approx 5.5 \\
    \sigma &\approx 1.833 \\
    combined_\sigma &\approx 1.833 \\
    effect\_{size} &= 5 / 1.833 \\
    &= 2.7277
\end{align}
$$

![Power analysis](./images/Power_analysis_distributions.png)

But the author of the paper mentions that the number of trajectories that were generated during the research was 10000, for both forward and backward trajectories, so that was the number used for curation of this dataset as well.

### Exploratory data analysis

Exploratory data analysis has been conducted and the analysis can be found on `Dataset Analysis.ipynb`.

A plot showing one of the forward trajectories of the particle:

![Forward trajectory](./images/anim0.gif)

The moving parabola is the harmonic energy function as a function of the x-coordinate of the particle. The center of the harmonic well moves with a constant speed in the x-direction.

Backward trajectory:

![Backward trajectory](./images/anim1.gif)

The forward and backward work distributions as plotted in the original paper has also been done in the analysis notebook. The graph is shown below:

![Work distributions](./images/work_distribution_graph.png)

The above graph can be explained with the crook's fluctuation theorem. The theorem simply states the following relation:

$$
\begin{align}
    \frac{\rho_F(w)}{\rho_B(-w)} = e^{w - \Delta F}
\end{align}
$$

When $w = \Delta F$, the RHS becomes 1, and that's when the forward and backward distributions meet. For this particular example, since it's only the harmonic potential centers that shift, the free energy difference between the two states (State A:  $\lambda = 0$ State B: $\lambda = 5$) is zero. So the two probability distributions should intersect at 0, which is shown.

### Link to public dataset

The dataset is hosted on huggingface. It can be found [here](https://huggingface.co/datasets/skbadani/BrownianTimeSeries).

### Ethics statement

This synthetic dataset has been curated while adhering to ethical principles, while trying to mimic the motion of a brownian particle in the real world as closely as possible. The dataset can be regenerated with the scripts provided, to ensure that simulation techniques have been used to generate the dataset instead of cherry-picking random values. However, if the dataset is regenerated, while some of the values may change, due to ergodicity, the work distributions would still be similar to the images displayed in the documentation. All attempts have been made to avoid biases while curating the dataset, and has been curated with the intent to promote responsible research and development practices.

### Open source license

The license used for this dataset is the [Open Data Commons Open Database License v1.0](https://choosealicense.com/licenses/odbl-1.0/). The License file is attached with the repo.