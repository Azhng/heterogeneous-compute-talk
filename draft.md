# Massive Parallelism with modern GPU


## Abstract

Single core performance in modern chips has not recieved any significant improvement for years. This is definitely a bad news for computation intensive programs. However, the level of parallalism within today's hardware is significantly higher than what we used to have. Number of computation cores within a chip has gone from merely two or four to ranges of thousands. Nevertheless, it is up to us, the developers, to fully exploit this high level of parallelism. In my talk: Massive Parallelism with modern GPU, I will introduce the way to significantly improve program performance by exploiting the parallelism in the hardware via OpenCL (Open Computing Language). OpenCL introduces a different programming architecture and memory model compared to what most of the developers are used to. It is powerful enough to horizontally scale up to thousands of computing cores, and it is also flexible enough to run on top of most of the modern platforms (CPU, GPU, FPGA or ASIC). The audience will be introduced to the OpenCL programming architecture and the basics of its memory model, few examples of how OpenCL programming architecture maps to different physical hardwares and a live demo of how to exploiting special features within the hardware to gain significant boost in performance.

## Timeline

* 1 min: Introduction
* 4 min: Introduction to OpenCL programming architecture
    * host-device architecture
    * command queue model
    * host vs device-side memory model
    * events
* 5 min: OpenCL hardware mapping
    * Multi-core CPU
    * Modern GPU (Radeon GCN GPU)
* 3 mins: live demo (image clustering use SURF image features)
    * naive CPU implementation
    * naive GPU implementation
    * GPU implementation with optimized memory access parttern
* 2 mins: Conclusion
    * advanced application of OpenCL
    * alternatives to OpenCL

## Q & A

Question: "Why do you want to talk at StarCon?"

Answer:
I believe the best way of mastering a new topic is to teach it to someone else. Personally, I have been learning about GPGPU computing (general purpose GPU computing) for a long time by myself. I have spent countless nights reading through books and the white paper published by hardware manufactures. I want to share all the knowledge I gained throughout this time and also during this process, solidify my own understandings.
Personally, I am a firm believer in that old saying: "Whatever doesn't kill you will only make you stronger". As a first time speaker myself, I want to get out of my own comfort zone and to challenge myself with the things that I have never tried before. Even though I did some quick lighting talks at my previous company, I have never had any opportunity to present in front of a large audience. I am very glad that there are conferences like StarCon that are very friendly towards to first time speakers. It provides us with a wonderful platforms to improve ourselves without constantly doubting that are we good enough to even apply as a speaker.
And lastly, as a broke CS undergrad, $100 compensation, FREE food and FREE ticket are very effective incentives :P
