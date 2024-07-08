---
permalink: /presentations/is-it-still-worth-it-to-learn-to-code
youtube: https://youtu.be/JMK_30jeGww
---
To watch: [YouTube Link](https://youtu.be/JMK_30jeGww)
# Is it still worth it to learn to code?

I've been asked a lot lately about my thoughts on the future of Software Engineering. Whenever a new AI advance is released, I get a flood of people asking about the future for software developers.
- The question they're asking isn't "Will I still be allowed to write software in the future?" - Everything besides C will still be legal.
- It's really, "Will I still be able to get paid with the skills I'm learning while I learn to code?"

The first thing I want to say is that I hate predicting things, particularly in public. If you would have asked me five years ago if any of the AI tech that we see today would have been feasible, I would have surely predicted no. And I'm not talking the hyped demos, I'm just saying conversational AI that returns somewhat reasonable (even if being completely wrong hallucinated) responses. So I have had to update my priors many times throughout the last few years regarding AI and it's capabilities (and thus future capabilities as well).

So I don't have enough hubris to think that I know what's going to happen in the future... but I do have just enough hubris to make a video about my thoughts ;)

So I have two major points I want to talk about:
- Software ⊃ coding
- Programming ⊃ coding

Before I give my thoughts, for the sake of argument I'll concede that:
- AI will be able to do all the coding tasks that a junior engineer is currently expected to do
- AI will be able to perform these tasks with the same/better speed & cost as a junior engineer
- AI will be able to do this and "production-ized" to do this quickly (say, around five years - I realize some people expect this in six months, but the rollout seems quite difficult to imagine in six months. We can have that conversation in a separate video)

If you think any of these points are too aggressive in favor of AI, that should only bolster the case I'm trying to make :)


When I say `coding` for the rest of the video, I'm referring to the act of sitting in front of your computer and typing/autocompleting/copy-pasting a programming language into an editor and then shipping to prod. In some sense, the exclusively "physical" act of creating software.

# Software ⊃ Coding

People don't pay for code. And they definitely don't pay to watch you just sit there and type things (ok... maybe they do if you're a Twitch Stream?)

They pay to have problems solved.

When you're coding, you're not getting paid for the code your write - you're getting paid to solve somebody's problems: real or perceived.
- Those problems might be for a client
- They could be for your boss
- They could be for other developers
- But the reason you're getting paid is because the problem you're solving for someone is valuable enough for them to part with beloved cash.
	- This boils down to software being able to provide something is that's faster, cheaper, more reliable than what could have been accomplished previously.

I'm going to consider software a superset of these coding tasks - you need much more than good algorithms to create value for your customers.
- Understanding requirements (and updating them when things change)
	- Talking to clients
- Communication
	- Understanding non-technical aspects communicated to you (a.k.a LISTENING) in their area of expertise
	- Communicating technical concepts to non-technical people in your area of expertise
- Saying no to feature creep / doing scope management
- Saying no to something you'd like to do, but think is likely to cost more than it's worth (rewrite everything in Rust)
- Social
	- Listening to feedback. Giving constructive feedback.
	- Mentoring
	- Patience, Kindness and Respect
- Asking and understanding "How do we make money"

The best software developers I ever worked with were really great at all of these things. Not just great at coding, but they understood each of these and helped me learn how to do them all better.

All of these skills will still be useful as long as we have jobs to do. And they are all skills that you can practice and hone while working as a software developer - regardless of your seniority and tech stack.

# Programming ⊃ Coding

- This section should likely be titled "Programming ***can be*** a superset of a coding"
- If I'm being very reductionist (and I mean VERY reductionist), I see two categories of programmers:
	- Solution Copiers
	- Problem Solvers

Solution Copiers is not exclusively about using copy-paste solutions. It's about using copy-paste solutions for copy-paste problems, **without examination**.
- As a clarification, there are a lot of people who primarily "copy-paste" code and solve a lot of problems.
	- Maybe they're running a scrappy solo startup.
	- Or maybe they are a non-programmer using Excel and copy-pasted python scripts to power some ridiculous real estate empire.
	- That's actually not the group of people I'm talking about here. These people are still problem-solvers - they are just focusing on a different part of solving problems.
- The Solution Copiers aren't interested in **how** things work, just getting past the next task.
	- Unaware of the ways in which the libraries, languages and tools they use solve problems (and where they don't!). Just copy paste the first solution from a stackoverflow problem or whatever their favorite LLM replies with until CI is green.
	- (But this isn't limited just to technical problems - as we've been talking about)
	- Not interested in learning how their business works or makes money or what their customers want.
	- Never considered the structure of their own organization and if it helps or hurts accomplishing the goals being set forth.


Now, the Problem Solvers: Curious people who try to solve problems via understanding, I think those skills will remain useful even if we never write a single line of code again.
- I think people are often underestimating the skills that they **CAN** learn via software development (emphasis on the **can**, since my whole point is that it's possible to be writing code for a long time and never learn any of these skills or make any progress).
	- Logical Thinking
	- Decomposing large problems into smaller ones
	- Recognizing, iterating on and solving issues for customers that they're willing to pay for
	- Domain analysis (as in, problem domains / domain logic / business logic)
	- Predicting edge-cases / failure-modes 
	- Trade-off management
	- Pattern recognition

All of these skills seem to me to be like muscles that you can train and get better at. And you can use software development as a vehicle for doing that training. And all of these skills are going to be useful for as long as we have jobs to do - same with all the of the soft skills I mentioned in the Software section.

- I'll give you an example:
	- A tale of two Neovimmers
		- A lot of people think Neovim is just "wasting time learning useless stuff". And that's fine! If they don't like Neovim, that's OK :) 
		- BUT, I want to give a quick parable about two different people using Neovim - this is not an exhaustive list, just two examples.
		- The first person tries out Neovim because of some extrinsic reason. They are hurried to get to step 1 of using Neovim, and don't take time to read/understand/explore. Something breaks in their config. They just post on Reddit until someone posts a reply with a solution. They make an issue with no reproduction steps. etc. We've seen this kind of person in every dev community, so you can probably relate.
			- In my opinion, this person is actually wasting their time with Neovim (which by the way is OK, we all like to waste time in different ways - I like playing Stardew Valley with my wife. And we waste time together and it's really nice (pacman users wouldn't understand)).
			- However, there isn't any learning going on throughout this experience  - which is bad if this characterizes **every** interaction you have with the skills that characterize your field.
		- Compare this to someone who enjoys using Neovim. They learn to understand how to read documentation. They learn a new programming language. They learn new idioms and APIs that can teach them about software design.
			- When something breaks in their configuration, they read the error message. They learn to debug software systems. They learn about rolling back, about lockfiles. They create a PR to fix the problem.
			- They build solutions for themselves and are able to rapidly iterate on them towards something that solves a real-world problem for them - They are their own customer.
			- This person has learned a lot, even if they end up with exactly the same code as person 1.
		- Both people spent a lot of time "on neovim". The first was a solution copier, the second a problem solver.
			- The skills, attitudes and perspectives characterizing the problem solver are helpful in many other domains - even if AI takes over writing software for them forever and they never get to use a modal text editor again.
			- You can replace Neovim with whatever other technology you want. React, Svelte, Rust, HTMX, Excel, whatever. It doesn't matter. The pattern is the same.
- My point is that **you** get to choose about how you are going to tackle problems and the takeaways that you'll have from actually solving that problem. To move from copy-paster to "gigachad problem solver" (as someone in my chat put it) largely revolves around you deciding to start thinking and asking questions today. That's pretty much it. Then you make the same choice tomorrow and the day after that. And then you keep doing that.
	- In practical terms, I would say you could try and build something where you are the customer and it solves some problem that you actually have.
	- Something difficult when you are making a product for other people - particularly when you're new - is distinguishing good feedback from loud feedback. It's common to have some loud feedback that seems to overwhelm and outweigh any other signal you're getting. The nice thing about making projects primarily for yourself is you get to the loud and obnoxious user.
	- Then eventually, you'll find out if you solved your problem or not. If you didn't, you iterate. As I tell my three-year-old son, "It's OK to fail. That's part of how we learn. The important part is that we use our roughness and our toughness to try again".

# Conclusion

In conclusion, I want to make it clear that I'm not saying Solution Copiers are bad people or that I don't like them. Instead, I am trying to communicate that I would be much more concerned if all the skills that I have developed revolved around regurgitating existing solutions - that's an area that I think is likely to be automated by AI in some fashion (and more quickly than other areas of software development).
 - I don't like giving advice on the internet because life is generally much too complicated for the person requesting help to adequately explain their situation and then too complicated for me to give a good answer and then still too complicated for them to understand the advice I'm giving without additional context.
 - Despite this, advice like "Be Curious", "Pay attention", "Work hard", "Don't be afraid to fail" have never led me astray. Thinking this way IMO gives someone the best chance at success - regardless of how quickly and thoroughly AI expands into software or other fields.

I don't know what the future is going to look like. I'm just a regular mortal. I put my pants on two legs at time. But I do think, even discounting all the arguments I've made throughout the video, that if your current hypothesis is that billions of new lines of code will be generated, it seems likely that understanding some things about code - not everything, not every language, not every framework, but just some things about software - will be a beneficial skill relative to other possible skills you might want to learn. Particularly, if you like learning about it and want to get really good at it.